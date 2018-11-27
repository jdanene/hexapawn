#pragma once
#include "model.h"

namespace hexapawn {


    //Current Pawns selected
    struct PawnSelect{
        ge211::Position pos;
        bool selected_p;

    };


// The radius of each rendered token.
    int const pawn_radius = 50;

// Colors of rendered pawns and board pieces.
    auto const p1_color          = ge211::Color(255,255,255, 230); // White
    auto const p2_color          = ge211::Color(0,0,0); // Black
    auto const ivory             = ge211::Color(250,235,215, 100);
    auto const brown             = ge211::Color(139,69,19);
    auto const first_move_color  = ge211::Color(255,255,255, 100);
    auto const second_move_color = ge211::Color(0,0,0, 100);

// The view class, which encapsulates rendering state and knowledge.
    class View
    {
    public:
        /// The view has const& access to the model--it can see it but cannot
        /// change it.
        explicit View(Model const&);

        /// Renders the current state of the model.
        void draw(ge211::Sprite_set&, ge211::Position, PawnSelect) const;

        /// The actual screen dimensions of the required game window.
        ge211::Dimensions screen_dimensions() const;

        /// Converts a logical board position to a physical screen position.
        ge211::Position board_to_screen(ge211::Position) const;

        /// Converts a physical screen position to a logical board position.
        ge211::Position screen_to_board(ge211::Position) const;

        //Todo: Add code that displays "Game Over"+str(winner) when the game is over.

    private:
        /// The model.
        Model const& m_model;

        /// The sprites
        ge211::Circle_sprite  m_player1_pawn{pawn_radius, p1_color};
        ge211::Circle_sprite  m_player2_pawn{pawn_radius, p2_color};
        ge211::Rectangle_sprite  m_ivory_square{{2*pawn_radius,2*pawn_radius}, ivory};
        ge211::Rectangle_sprite  m_brown_square{{2*pawn_radius,2*pawn_radius}, brown};
        ge211::Circle_sprite  m_p1PawnNoMove{pawn_radius, first_move_color};
        ge211::Circle_sprite  m_p2PawnNoMove{pawn_radius, second_move_color};

        /// Vector that holds the two background images used to create a checkered board
        std::vector<ge211::Rectangle_sprite> const m_background_vec{m_ivory_square,m_brown_square};


    };

} // end namespace connect4

