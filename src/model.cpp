#include "model.h"
#include <iostream>

using namespace ge211;

namespace hexapawn {



    Model::Model(int width, int height)
            : m_width(width), m_height(height)
    {
        //Smallest board size is 3x3
        assert(m_width > 2);
        assert(m_height > 2);

        //Largest board size is 8x8
        assert(m_width <= 8);
        assert(m_height <= 8);

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

    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }

    bool Model::player_move_goodp(ge211::Position old_pos, ge211::Position new_pos,Player whose_turn,\
    int (*pm)(int, int)) const
    {
        int old_row_no = old_pos.y;
        int old_col_no = old_pos.x;
        int new_row_no = new_pos.y;
        int new_col_no = new_pos.x;
        Player enemy_player = (whose_turn == Player::first) ? Player::second : Player::first;

        /*******************************************************************************
         * viable_row: the row that is one row forward of `old_pos.y`
         *      - If first player: viable_row = old_row_no - 1.
         *      - If second player: viable_row = old_row_no + 1.
         *      - In general: viable_row = pm(old_row_no,1)
         *          - `pm` is either 'add' or 'sub' depending on player.
         * left_kill:  the pawn that is one square diagonally to the left of `old_pos`
         * right_kill:  the pawn that is one square diagonally to the right of `old_pos`
         * no_kill: the pawn that is one square forward of `old_pos`
         * ****************************************************************************/
        int viable_row = pm(old_row_no,1);
        Position left_kill = {old_col_no - 1, viable_row};
        Position right_kill = {old_col_no + 1, viable_row};
        Position no_kill = {old_col_no, viable_row};
        Player player_at_left = get_ele(left_kill);
        Player player_at_right = get_ele(right_kill);
        Player player_at_no_kill = get_ele(no_kill);

        /********************** Enforcing Pawn Move (Invariant 3) *********************
         * - old_pos => `left_kill` iff there is an enemy pawn at `left_kill`
         *      - Interpretation: capture a pawn one square diagonally to the left
         * - old_pos => `right_kill` iff there is an enemy pawn at `right_kill`
         *      - Interpretation: capture a pawn one square diagonally to the right
         * - old_pos => `no_kill` iff there is an no pawn at `no_kill`
         *      - Interpretation: move pawn one square forward
         * - All other pawn moves are NOT VIABLE!
         * *************************************************************/
        // last_row:
        // - If first player: then the last row is 0.
        //      - Since the first player starts from the bottom of our grid [aka row =height() - 1]
        // - If second player: then the last row is height() - 1.
        //      - Since the second player starts from the top of our grid [aka row =0]
        int last_row = (whose_turn == Player::first) ? 0 : height() - 1;
        if (old_row_no == last_row) return false; // Can't move if at the other side of grid

        //The more general case
        if ((new_col_no == left_kill.x) && (new_row_no == left_kill.y)) {
            if (old_col_no == 0) return false; //Can't move left from a pawn that is all the way at the left
            return (player_at_left == enemy_player); //Can only perform a kill move if enemy pawn is at `left_kill`
        } else if ((new_col_no == right_kill.x) && (new_row_no == right_kill.y)) {
            if (old_col_no == width() - 1) return false; //Can't move right from a pawn that is all the way to  the right
            return (player_at_right == enemy_player);//Can only perform a kill move if enemy pawn is at `right_kill`
        } else if ((new_col_no == no_kill.x) && (new_row_no == no_kill.y)){
            return (player_at_no_kill == Player::neither); //Only move forward if no pawn is at position
        }else{
            return false;
        }
    }


    bool Model::is_viable_p(ge211::Position old_pos, ge211::Position new_pos, Player whose_turn) const
    {
        if (!bounds_check(old_pos) or !bounds_check(new_pos)) return false;
        switch (whose_turn) {
            case Player::first:
                return player_move_goodp(old_pos,new_pos,whose_turn,sub);
            case Player::second:
                return player_move_goodp(old_pos,new_pos,whose_turn,add);
            default:
                throw ge211::Client_logic_error("is_viable_p: not a player");
        }
    }

    bool Model::bounds_check(ge211::Position pos) const {
        return ((0 <= pos.y < height()) && (0 <= pos.x < width()));
    }

    const Player& Model::get_ele(ge211::Position pos) const
    {
        if  (bounds_check(pos)) return m_board[pos.y][pos.x];
        else throw ge211::Client_logic_error("get_ele: element out of bounds");
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
                else if (player == Player::second){
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
            // FixMe: No idea why this is saying the condition is always true
            m_winner = Player::neither;
            m_turn = Player::neither;}
        // A player has yet to win and so the game can continue => next player turn
        else{
            m_turn = (get_turn() == Player::first) ? Player::second : Player::first;
        }

    }

    void Model::place_pawn(ge211::Position old_pos, ge211::Position new_pos)
    {
        if (is_viable_p(old_pos,new_pos, get_turn())) {
            m_board[new_pos.y][new_pos.x] = m_turn;
            m_board[old_pos.y][old_pos.x] = Player::neither;
        }
    }


    }




