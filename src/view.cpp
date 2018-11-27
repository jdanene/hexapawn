#include "view.h"


namespace hexapawn {

    View::View(const Model& model)
            : m_model(model)
    { }


    void View::draw(ge211::Sprite_set& sprites, ge211::Position mouse_position, PawnSelect pawn_select) const
    {
        //Parameters
        auto len = m_background_vec.size();
        int idx = -1;
        Player current_player = m_model.get_turn();
        bool special_case_checkered = (not ((m_model.height()%2 == 1) && (m_model.height()%2 == 1))) ? true : false;


        //FixMe: Code is especially clunky to get around errors from ge211

        // Adding pawns to board and make the board checkered.
        // Differentiate opaqueness so that players know whose turn it is.
        for (int row_no = 0; row_no < m_model.height(); ++row_no) {
            if ((special_case_checkered) && (row_no%2 == 1)){
                ++idx;
            }else{
                --idx;
            }
            for (int col_no = 0; col_no < m_model.width(); ++col_no) {
                Player player = m_model.get_ele({col_no,row_no});
                // We treat Player::neither as empty space
                if (Player::neither != player) {
                    if (!pawn_select.selected_p) {
                        if (player == Player::first) {
                            auto const &sprite =
                                    player == current_player ? m_player1_pawn : m_p1PawnNoMove;
                            sprites.add_sprite(sprite, board_to_screen({col_no, row_no}), 1);
                        } else {
                            auto const &sprite =
                                    player == current_player ? m_player2_pawn : m_p2PawnNoMove;
                            sprites.add_sprite(sprite, board_to_screen({col_no, row_no}), 1);
                        }
                    } else if ((pawn_select.pos.x != col_no) or (pawn_select.pos.y != row_no)) {
                        if (player == Player::first) {
                            auto const& sprite =
                                    player == current_player ? m_player1_pawn : m_p1PawnNoMove;
                            sprites.add_sprite(sprite, board_to_screen({col_no, row_no}), 1);
                        } else {
                            auto const& sprite =
                                    player == current_player ? m_player2_pawn : m_p2PawnNoMove;
                            sprites.add_sprite(sprite, board_to_screen({col_no, row_no}), 1);
                        }
                    }
                }
                // Add ivory and brown squares to the board to make it checkered.
                // Using modulo so every other turn we add:
                // m_ivory_square => m_brown_square => m_ivory_square => m_brown_square ...

                //std::cout << "Curr idx Player turn is: "<< idx%len << "\n";
                //std::cout << "Curr x,y Player turn is: "<< col_no <<","<< row_no <<"\n";
                ++idx;
                sprites.add_sprite(m_background_vec.at(idx%len), board_to_screen({col_no, row_no}), 0);
            }
        }

        // Allows selected pawn to be moved around. Only happens if (selected_p == true),
        // aka the mouse pad is down and you have selected a viable pawn.
        int col = mouse_position.x;
        int row = mouse_position.y;
        if (pawn_select.selected_p){
            if (m_model.bounds_check(mouse_position)) {
                sprites.add_sprite(current_player == Player::first ? m_player1_pawn : m_player2_pawn, board_to_screen({col, row}), 2);
            }
        }
    }

    ge211::Position View::board_to_screen(ge211::Position board_pos) const
    {
        int x = 2 * pawn_radius * board_pos.x;
        int y = 2 * pawn_radius * (m_model.height() - board_pos.y - 1);
        //std::cout << "board_to_screen()"<<"{" <<board_pos.x << ","<< board_pos.y <<"}" << "\n";
        //std::cout << "board_to_screen()"<<"{" <<x << ","<< y <<"}" << "\n";
        return {x, y};
    }

    ge211::Position View::screen_to_board(ge211::Position screen_pos) const
    {
        int col_no = screen_pos.x / (2 * pawn_radius);
        int row_no = m_model.height() - screen_pos.y / (2 * pawn_radius) - 1;
        //std::cout << "screen_to_board()"<<"{" <<screen_pos.x << ","<< screen_pos.y <<"}" << "\n";
        //std::cout << "board_to_screen()"<<"{" <<col_no << ","<< row_no <<"}" << "\n";
        return {col_no, row_no};
    }


    ge211::Dimensions View::screen_dimensions() const
    {
        return {2 * pawn_radius * m_model.width(),
                2 * pawn_radius * m_model.height()};
    }

} // end namespace hexapawn