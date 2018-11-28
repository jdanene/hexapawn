#pragma once
#include <cassert>
#include <ge211.h>
#include <cmath>
#include <vector>


namespace hexapawn {


    ///How we represent players of the absence thereof.
    enum class Player
    {
        first, second, neither
    };

    // as_integer: enumeration -> number
    // So we can turn player enumeration class to integer whenever we want to
    template <typename Enumeration>
    auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
    {
        return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }

     // Models a hexapawn game. The parameters are `width' the width of the board,
     // `height' the height of the board.
    class Model
    {
    public:
        /*
         * Constructs a hexapawn-N-M game model. The default parameters give a standard
         * 3x3 hexapawn game. Otherwise:
         * \param `width' the width of the grid
         * \param `height' the height of the grid
        */
        explicit Model(int width, int height);

        ///Functions to get a view of private variables
        int width() const {return m_width; }
        int height() const {return m_height; }
        const Player& get_ele(ge211::Position) const; //Gets a view of a given element
        const Player& get_turn() const { return m_turn; }; // Returns whose turn it is, or Player::neither if game over.
        const Player& game_winner() const { return m_winner; }; // Returns the winner of game is there is one

        /// Checks if there is a pawn at the position.
        bool pawn_there_p(ge211::Position) const;

        ///Check if coordinates within bounds
        bool bounds_check(ge211::Position) const;

         /// Returns true if game is over
         bool game_over_p() const { return (Player::neither == m_turn) ; };

        /********************* (Invariant 1) Player Wins/Game Over Invariant ***********************
         *  game_over[1] - If a player has no valid moves then that player loses and the other player wins
         *  game_over[2] - If both players have no moves then neither player win
         *  game_over[3]- If a player gets a pawn to the other side then that player wins
         *******************************************************************************************/
    private:
        /// Returns true if there is at-least one feasible move for the pawn `p` located at `pos`
        // Aux function for `update_winner_and_turn`, helps enforce (Invariant 1)::game_over[1] && (Invariant 1)::game_over[2]
        bool feasible_moves_p(ge211::Position pos, Player p) const;
    public:
        /**************** (Invariant 2) Player Turn Invariant ***************************************
         * - If the game is not over
         *      -Then after a player enacts a valid pawn move then it is the other players turn.
         * - Else
         *      - Neither player has a turn
         ********************************************************************************************/

        /// Updates winner if there is one and updates the turn as well.
        // Enforces (Invariant 1) & (Invariant 2)
        void update_winner_and_turn();

        /********************** (Invariant 3) Player/Pawn Move Invariant *****************************
         * Valid Pawn moves
         *      - capture a pawn one square diagonally to the left
         *      - capture a pawn one square diagonally to the right
         *      - move pawn one square forward
         * Invalid Pawn moves
         *      - All moves not specified as valid.
         * ********************************************************************************************/
    private:
        /// Returns true if a move is viable for a specified player.
        //  Aux function for `is_viable_p`
        bool player_move_goodp(ge211::Position old_pos, ge211::Position new_pos,Player whose_turn,\
        int (*pm)(int, int)) const;
    public:
        /// Is the move from old_pos => new_pos viable or not?
        // Checks the conditions of (Invariant 3)
        bool is_viable_p(ge211::Position old_pos, ge211::Position new_pos, Player whose_turn) const;

        /// Places the pawn from old_pos to new_pos.
        //Enforces (Invariant 3)
        void place_pawn(ge211::Position old_pos, ge211::Position new_pos);

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

    };

}





