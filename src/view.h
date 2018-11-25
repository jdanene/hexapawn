#pragma once
#include <model.h>
#include <ge211.h>
#include <controller.h>

namespace hexapawn {

// The radius of each rendered token.
    int const pawn_radius = 50;

// Colors of rendered pawns and board pieces.
    ge211::Color const p1_color          = ge211::Color::white();
    ge211::Color const p2_color          = ge211::Color::black();
    ge211::Color const ivory             = ge211::Color::from_rgba(255,255,240);
    ge211::Color const brown             = ge211::Color::from_rgba(86,57,28);
    ge211::Color const first_move_color  = p1_color.lighten(0.3);
    ge211::Color const second_move_color = p2_color.lighten(0.3);

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

    private:
        /// The model.
        Model const& m_model;

        /// The sprites
        ge211::Circle_sprite const m_player1_pawn{pawn_radius, p1_color};
        ge211::Circle_sprite const m_player2_pawn{pawn_radius, p2_color};
        ge211::Rectangle_sprite const m_ivory_square{{2*pawn_radius,2*pawn_radius}, ivory};
        ge211::Rectangle_sprite const m_brown_square{{2*pawn_radius,2*pawn_radius}, brown};
        ge211::Circle_sprite const m_p1PawnNoMove{pawn_radius, first_move_color};
        ge211::Circle_sprite const m_p2PawnNoMove{pawn_radius, second_move_color};

        /// Vector that holds the two background images used to create a checkered board
        std::vector<ge211::Rectangle_sprite> m_background_vec{m_ivory_square, m_brown_square};

    };

} // end namespace connect4

