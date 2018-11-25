#pragma once
#include <ge211.h>
#include <model.h>
#include <view.h>

/// Main function is to advance the state-space

namespace hexapawn {

    //Current Pawns selected
    struct PawnSelect{
        ge211::Position pos;
        bool selected_p;

    };

    // Inheriting the abstract_game class into the contoller.
    class Controller : public ge211::Abstract_game
    {
    public:
        // Constructor for the controller. This M-V-C model is contrary to connect4
        // The controller gets in data and sends it to the model only. The controller
        // can view the data from the view but can not change it.
        explicit Controller(size_t width = 3, size_t height = 3);

    protected:
        /* In graphics the origin is at the upper left. x-corr increase to right and
         * y-corr increases downward.
         * */

        /// Override the initial_window_dimensions() function to specify the initial dimensions of the game's
        /// window. This is only be changes by the engine once at startup.
        /// Note that this modifies the game-engine, it is constant because it can't modify
        /// the data members of the class.
        ge211::Dimensions initial_window_dimensions() const override;

        // Just gives the window a title
        std::string initial_window_title() const override;

        // Every time the mouse moves
        void on_mouse_move(ge211::Position) override;

        // When you hold the mouse button down you select a piece.
        void on_mouse_down(ge211::Mouse_button, ge211::Position) override;

        // When you release the mouse you put down the selected pawn.
        void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

        //Overrides the draw function given by ge211::Abstract_game
        void draw(ge211::Sprite_set&) override;

    private:
        Model m_model;
        View m_view;

        // Logical board column where the mouse was last seen.
        ge211::Position m_mouse_position;


        PawnSelect m_selected_pawn;

    };
}