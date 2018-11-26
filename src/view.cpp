#include <view.h>


namespace hexapawn {

    View::View(const Model& model)
            : m_model(model)
    { }


    void View::draw(ge211::Sprite_set& sprites, ge211::Position mouse_position, PawnSelect pawn_select) const
    {
        //Parameters
        size_t len = m_background_vec.size();
        int idx = -1;
        Player current_player = m_model.get_turn();
        ge211::Circle_sprite p1_pawn = (current_player == Player::first) ?  m_player1_pawn : m_p1PawnNoMove;
        ge211::Circle_sprite p2_pawn = (current_player == Player::second) ?  m_player2_pawn : m_p2PawnNoMove;

        // Adding pawns to board and make the board checkered.
        // Differentiate opaqueness so that players know whose turn it is.
        for (int row_no = 0; row_no < m_model.height(); ++row_no) {
            for (int col_no = 0; col_no < m_model.width(); ++col_no) {
                Player player = m_model.get_ele({col_no,row_no});

                // We treat Player::neither as empty space
                if (player != Player::neither)
                {
                    //Conditions for a pawn that has been selected. If selected aka (pawn_select.selected_p == t)
                    // then don't draw, otherwise we draw since (pawn_select.selected_p == f) means a pawn has not been selected.
                    if ((pawn_select.pos.x == col_no) && (pawn_select.pos.y == row_no)){
                        if (!pawn_select.selected_p)
                        {
                            auto const& sprite = (player == Player::first) ? p1_pawn : p2_pawn;
                            sprites.add_sprite(sprite, board_to_screen({col_no, row_no}), 1);
                        }
                    }
                    else{
                        auto const& sprite = (player == Player::first) ? p1_pawn : p2_pawn;
                        sprites.add_sprite(sprite, board_to_screen({col_no, row_no}), 1);
                    }
                }
                // Add ivory and brown squares to the board to make it checkered.
                // Using modulo so every other turn we add:
                // m_ivory_square => m_brown_square => m_ivory_square => m_brown_square ...
                ++idx;
                sprites.add_sprite(m_background_vec[idx%len], board_to_screen({col_no, row_no}), 0);
            }
        }

        // Allows selected pawn to be moved around. Only happens if (selected_p == true),
        // aka the mouse pad is down and you have selected a viable pawn.
        int col = mouse_position.x;
        int row = mouse_position.y;
        if (pawn_select.selected_p){
            if (row < m_model.height() && col < m_model.width()) {
                auto const& sprite = (m_model.get_turn() == Player::first) ? p1_pawn : p2_pawn;
                sprites.add_sprite(sprite, board_to_screen({col, row}), 2);
            }

        }
    }

    ge211::Position View::board_to_screen(ge211::Position board_pos) const
    {
        int x = 2 * pawn_radius * board_pos.x;
        int y = 2 * pawn_radius * (m_model.height() - board_pos.y - 1);
        return {x, y};
    }

    ge211::Position View::screen_to_board(ge211::Position screen_pos) const
    {
        int col_no = screen_pos.x / (2 * pawn_radius);
        int row_no = m_model.height() - screen_pos.y / (2 * pawn_radius) - 1;
        return {col_no, row_no};
    }


    ge211::Dimensions View::screen_dimensions() const
    {
        return {2 * pawn_radius * m_model.width(),
                2 * pawn_radius * m_model.height()};
    }

} // end namespace hexapawn