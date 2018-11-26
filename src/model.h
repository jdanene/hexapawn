#pragma once
#include <ge211.h>
#include <cassert>
#include <ge211.h>
#include <cmath>


namespace hexapawn {


    ///How we represent players of the absence thereof.
    enum class Player
    {
        first, second, neither
    };

     // Models a hexapawn game. There parameters are `width' the width of the board,
     // `height' the height of the board.
    class Model
    {
    public:
        /*
         * Constructs a hexapawn-N-M game model. The default parameters give a standard
         * 3x3 hexapawn game. Otherwise:
         *
         * \param `width' the width of the grid
         * \param `height' the height of the grid
        */
        explicit Model(int width, int height);

        ///Functions to get a view of private variables
        int width() const {return m_width; }
        int height() const {return m_height; }

        ///Gets a view of a given element
        const Player& get_ele(ge211::Position) const;

        /// Checks if there is a pawn at the position.
        bool pawn_there_p(ge211::Position) const;

        /// Is the move from old_pos => new_pos viable or not? Checks the preconditions of the game
        bool is_viable_p(ge211::Position old_pos, ge211::Position new_pos, Player whose_turn) const;

        /// Places the pawn from old_pos to new_pos.
        void place_pawn(ge211::Position old_pos, ge211::Position new_pos);

        /// Returns whose turn it is, or Player::neither for game over.
        const Player& get_turn() const { return m_turn; };

        ///Return the winner, or Player::neither  for stalemates or when the game is not over yet.
        //const Player& game_over() const { return m_winner; };

        /* **********************************************************************
         ************************ Game Invariant ********************************
         *  Invariant 1 - If a player has no moves then that player loses and the other player wins
         *  Invariant 2 - If both players have no moves then neither player win
         *  Invariant 3 - If a player gets a pawn to the other side then that player wins
         * **********************************************************************/
        //
        // Private helpers:
        //

        /// Updates winner if there is one and updates the turn as well. This function also enforces the invariant
        void update_winner_and_turn();

    private:
        ///The game parameters
        int const m_width;
        int const m_height;

        /// The board itself.
        std::vector<std::vector<Player>> m_board;

        ///The current turn
        Player m_turn = Player::first;

        /// The winning player, if any
        Player m_winner = Player::neither;

        /// Aux function for `is_viable_p` returns true or false if a move is viable for a specific player.
        bool player_move_goodp(ge211::Position old_pos, ge211::Position new_pos,\
        int (*pm)(int, int),bool (*ineq)(int, int)) const;

        /// Returns true if there exits a feasible move for the pawn `p` located at `pos`
        bool feasible_moves_p(ge211::Position pos, Player p) const;
    };

}





