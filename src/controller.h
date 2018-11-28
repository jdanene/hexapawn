#pragma once
#include "model.h"
#include "view.h"


namespace hexapawn {

    /// Inheriting the abstract_game class into the controller.
    class Controller : public ge211::Abstract_game
    {
    public:
        /// The controller for hexapawn game
        explicit Controller(int width = 3, int height = 3);

    protected:

        /// Override the initial_window_dimensions() function to specify the initial dimensions of the game's window.
        ge211::Dimensions initial_window_dimensions() const override;

        /// Just gives the window a title
        std::string initial_window_title() const override;

        /// Overrides the on_mouse_move  given by ge211::Abstract_game
        void on_mouse_move(ge211::Position) override;

        /// Overrides the on_mouse_down  given by ge211::Abstract_game
        void on_mouse_down(ge211::Mouse_button, ge211::Position) override;

        /// Overrides the on_mouse_up  given by ge211::Abstract_game
        void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

        ///Overrides the draw function given by ge211::Abstract_game
        void draw(ge211::Sprite_set&) override;

    private:
        /// Private class members
        Model m_model;
        View m_view;

        /// Logical board column where the mouse was last seen.
        ge211::Position m_mouse_position;

        /// Records the pawns that have been selected
        PawnSelect m_selected_pawn;

    };
}