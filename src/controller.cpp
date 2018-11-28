#include "controller.h"
using namespace ge211;


namespace hexapawn {

    Controller::Controller(int width, int height)
            : m_model(width, height)
            , m_view(m_model)
            , m_mouse_position(-1,-1)
            , m_selected_pawn{{-1, -1},false}
    { }

    void Controller::draw(Sprite_set& set)
    {
        if (m_model.game_over_p()){
           m_view.drawGameOver(set);
        } else{
            m_view.draw(set, m_mouse_position, m_selected_pawn);
        }

    }


    Dimensions Controller::initial_window_dimensions() const
    {
        return m_view.screen_dimensions();
    }

    std::string Controller::initial_window_title() const
    {
        return "Hexapawn!";
    }

    void Controller::on_mouse_move(Position screen_pos)
    {
        m_mouse_position = m_view.screen_to_board(screen_pos);
    }

    void Controller::on_mouse_down(Mouse_button btn, Position screen_posn)
    {
        if (m_model.game_over_p()) return;

        // The left mouse button corresponds to the mouse pad.
        if (btn != Mouse_button::left) return;

        Position board_pos = m_view.screen_to_board(screen_posn);

        //If the selected pawn is in the bounds of the game then process it.
        if (m_model.bounds_check(board_pos))  {
            // Can only select a pawn that corresponds to the current turn
            if (m_model.get_turn() ==  m_model.get_ele(board_pos)){
                // Can only select a pawn if there is a pawn at the selected position.
                if (m_model.pawn_there_p(board_pos)) {
                    //Store the selected pawn
                    m_selected_pawn.pos = board_pos;
                    //Indicate a pawn has been selected
                    m_selected_pawn.selected_p = true;
                }
            }
        }
    }

    void Controller::on_mouse_up(Mouse_button btn, Position screen_posn)
    {
        if (m_model.get_turn() == Player::neither) return;
        if (btn != Mouse_button::left) return;

        Position board_pos = m_view.screen_to_board(screen_posn);

        //If the pawn is not viable deselect then do nothing
        if (!m_model.is_viable_p(m_selected_pawn.pos,board_pos,m_model.get_turn())){
            m_selected_pawn.selected_p = false;
            return;
        }

        // State Transition: New Turn, Check Winner, New Board Arrangement
        if (board_pos.x < m_model.width() && board_pos.y < m_model.height()) {
            //Update the grid/board game state by moving the selected pawn to the new position.
            m_model.place_pawn(m_selected_pawn.pos,board_pos);
            //Update the rest of the game states: turn, winner
            m_model.update_winner_and_turn();
        }

        //Update indicator to signify that there isn't a pawn currently selected.
        m_selected_pawn.selected_p = false;

    }






}
