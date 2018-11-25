#include <model.h>


using namespace ge211;

namespace hexapawn {



    Model::Model(int width, int height)
            : m_width(width), m_height(height)
    {
        assert(m_width > 1);
        assert(m_height > 1);

        //Initialize the logical grid.
        std::vector<Player> p1_row(m_width,Player::first);
        std::vector<Player> p2_row(m_width,Player::second);
        std::vector<Player> blank_row(m_width,Player::neither);

        for (int row_no = 0; row_no < m_height; ++row_no) {
            if (row_no == m_height - 1){
                m_board.emplace_back(p1_row);
            }else if (row_no == 0){
                m_board.emplace_back(p2_row);
            }else{
                m_board.emplace_back(blank_row);
            }
        }

    }

    bool Model::player_move_goodp(ge211::Position old_pos, ge211::Position new_pos,\
    int (*pm)(int, int),bool (*ineq)(int, int)) const
    {
        int old_row_no = old_pos.y;
        int old_col_no = old_pos.x;
        int new_row_no = new_pos.y;
        int new_col_no = new_pos.x;
        Player other_player = (get_turn() == Player::first) ? Player::second : Player::first;

        // last_row:
        // - first player then the last row is 0. Since the first player starts from the bottom of our grid
        // - second player then the last row is height() - 1. Since the second player starts from the top of our grid
        int last_row = (get_turn() == Player::first) ? 0 : height() - 1;
        if (old_row_no == last_row) return false; // Can't move if at the other side of grid

        // Subtract/Add:
        // - first player it is old_row_no-1.
        // - second player it is old_row_no+1.
        // Same reasoning given for comment `last_row`
        int viable_row = pm(old_row_no,1);
        Position viable_left_kill = {old_col_no - 1, viable_row};
        Position viable_right_kill = {old_col_no + 1, viable_row};
        Position viable_no_kill = {old_col_no, viable_row};
        Player player_at_left = m_board[viable_left_kill.y][viable_left_kill.x];
        Player player_at_right = m_board[viable_right_kill.y][viable_right_kill.x];
        Player player_at_no_kill = m_board[viable_no_kill.y][viable_no_kill.x];

        //Can't move up/down too far [col], can't move left/right too far [row], can't stay in same place or move backwards
        //  inequality 1:
        //      - first player it is <
        //      - second player it is >
        //  inequality 3:
        //      -first player it is !<
        //      - for second player it is !<
        // Same reasoning given for comment `last_row`
        if ((ineq(new_row_no,viable_row)) or (std::abs(new_col_no - old_col_no) > 1)
            or !ineq(new_row_no,old_row_no)) return false;

        //The more general case
        if ((new_col_no == viable_left_kill.x) && (new_row_no == viable_left_kill.y)) {
            if (old_col_no == 0) return false; //Can't move left from a pawn that is all the way at the left
            return (player_at_left == other_player); //Can perform a kill move only if another player pawn is at position
        } else if ((new_col_no == viable_right_kill.x) && (new_row_no == viable_right_kill.y)) {
            if (old_col_no == width() - 1) return false; //Can't move left from a pawn  if all the way at the right
            return (player_at_right == other_player);//Kill move only if another player pawn is at position
        } else {
            return (player_at_no_kill == Player::neither); //Only move forward if no pawn is at position
        }
    }

    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }
    bool less(int a, int b) { return a < b; }
    bool greater(int a, int b) { return a > b; }

    bool Model::is_viable_p(ge211::Position old_pos, ge211::Position new_pos, Player whose_turn) const
    {
        switch (whose_turn) {
            case Player::first:
                return player_move_goodp(old_pos,new_pos,sub,less);
            case Player::second:
                return player_move_goodp(old_pos,new_pos,add,greater);
            default:
                throw ge211::Client_logic_error("other_player: not a player");
        }
    }

    const Player& Model::get_ele(ge211::Position pos) const
    {
        return m_board[pos.y][pos.x];
    }

    bool Model::pawn_there_p(ge211::Position pos) const
    {
        return (get_ele(pos) != Player::neither);
    }

    bool Model::feasible_moves_p(ge211::Position pos, Player p) const
    {
        int new_y = (Player::first == p) ? pos.y-1 : pos.y+1;
        ge211::Position up_move =  {pos.x,new_y};
        ge211::Position left_move = {pos.x-1,new_y};
        ge211::Position right_move = {pos.x+1,new_y};
        return (is_viable_p(pos,up_move, p) or is_viable_p(pos,left_move, p) or is_viable_p(pos,right_move, p));
    }

    void Model::update_winner_and_turn()
    {
        bool p1_hasmoves_p = false;
        bool p2_hasmoves_p = false;
        bool p1_wins = false;
        bool p2_wins = false;
        ge211::Position pos(-1,-1);
        Player player;

        // Loop through grid entries and check if a player has moves available or if a pawn has reached
        // the other side.
        for (int row_no = 0; row_no < height(); ++row_no) {
            for (int col_no = 0; col_no < width(); ++col_no) {
                pos = {col_no,row_no};
                player = get_ele(pos);
                if (player == Player::first){
                    p1_hasmoves_p = (feasible_moves_p(pos,player) or p1_hasmoves_p);
                    // Check if first player has reached the other side
                    if (row_no == 0){
                        p1_wins = true;
                        break;}
                }
                if (player == Player::second){
                    p2_hasmoves_p = (feasible_moves_p(pos,player) or p2_hasmoves_p);
                    // Check if second player has reached the other side
                    if (row_no == height()-1){
                        p2_wins = true;
                        break; }
                }
            }
        }

        // Enforcing Invariants
        if (p1_wins) {
            m_winner=Player::first;
            m_turn = Player::neither;}
        else if (p2_wins) {
            m_winner=Player::second;
            m_turn = Player::neither; }
        else if (!p1_hasmoves_p && p2_hasmoves_p) {
            m_winner = Player::second;
            m_turn = Player::neither;}
        else if (p1_hasmoves_p && !p2_hasmoves_p) {
            m_winner = Player::first;
            m_turn = Player::neither;}
        else if (!p1_hasmoves_p  && !p2_hasmoves_p) {
            m_winner = Player::neither;
            m_turn = Player::neither;}
        // A player has yet to win and so the game can continue => next player turn
        else{
            m_turn = (get_turn() == Player::first) ? Player::second : Player::first;
        }

    }

    void Model::place_pawn(ge211::Position old_pos, ge211::Position new_pos)
    {
        if (is_viable_p(old_pos,new_pos, get_turn()))
        {
            m_board[new_pos.y][new_pos.x] = get_turn();
            m_board[old_pos.y][old_pos.x] = Player::neither;
        }
    }




}