#include <controller.h>
using namespace ge211;


namespace hexapawn {

    Controller::Controller(size_t width, size_t height)
            : m_model(width, height)
            , m_view(m_model)
            , m_mouse_position(-1,-1)
            , m_selected_pawn{{-1, -1},false}
    { }

    void Controller::draw(Sprite_set& set)
    {
        m_view.draw(set, m_mouse_position, m_selected_pawn);
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
        // Basically this clause happens if the game is over
        if (m_model.get_turn() == Player::neither) return;

        // The left mouse button corresponds to pthe mouse pad.
        if (btn != Mouse_button::left) return;

        Position board_pos = m_view.screen_to_board(screen_posn);

        //If the selected pawn is in the bounds of the game then process it.
        if (board_pos.y < m_model.height() && board_pos.x < m_model.width()) {
            // Can only select a pawn if there is a pawn at the selected position.
            if (m_model.pawn_there_p(board_pos))
            {
                //Store the selected pawn
                m_selected_pawn.pos = board_pos;
                //Indicate a pawn has been selected
                m_selected_pawn.selected_p = true;
            }
        }
    }

    void Controller::on_mouse_up(Mouse_button btn, Position screen_posn)
    {
        // Basically this clause happens if the game is over
        if (m_model.get_turn() == Player::neither) return;
        // The left mouse button corresponds to the mouse pad.
        if (btn != Mouse_button::left) return;

        Position board_pos = m_view.screen_to_board(screen_posn);

        //If the pawn is not viable do nothing
        if (!m_model.is_viable_p(m_selected_pawn.pos,board_pos,m_model.get_turn())) return;

        // State Transition: New Turn, Check Winner, New Board Arrangement
        if (board_pos.x < m_model.width() && board_pos.y < m_model.height()) {
            //Move the selected pawn to the new position.
            m_model.place_pawn(m_selected_pawn.pos,board_pos);
            //Update the rest of the game states
            m_model.update_winner_and_turn();
        }

        //Update indicator to signify that there is no pawn currently selected.
        m_selected_pawn.selected_p = false;

    }






}
