#pragma once

#include <ge211.h>

namespace hexapawn {

    //How we represent players of the absence thereof.
    enum class Player
    {
        first, second, neither
    };

    /*
     *  Returns the other player, if given Player::first or Player::second ;
     *  throws ge211::Client_logic_error if given PLayer::neither
    */
    Player other_player(Player);

    /*
     * Models a hexapawn game. There parameters are `width' the width of the board,
     * `height' the height of the board.
    */
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
        explicit Model(int width = 3, int height = 3);

        //Functions to get a view of private variables
        int width() const {return width_; }
        int height() const {return height_; }


        //Gets a view of the given column
        // **Precondition:** `0 <= col_no < height()`
        const std::vector<Player>& get_column(int col_no) const;
        const std::vector<Player>& get_row(int col_no) const;

        // Places the pawn for a given player in the given row, column
        // Provided that the
        void place_pawn(int row_no, int col_no);

        // Is the move viable or not? Checks the preconditions of the game
        bool is_viable(int row_no, int col_no);

        // Returns whose turn it is, or Player::neither for game over.
        Player get_turn() const { return turn_; };

        //Return the winner, or Player::neither  for statemeates or when the game is not over yet.
        Player game_over() const { return winner_; };



    private:
        //The game parameters
        int width_;
        int height_;

        //The current turn
        Player turn_ = Player::first;

        // The winning player, if any
        Player winner_ = Player::neither;

        // The board itself.
        std::vector<std::vector<Player>> board_;

        // INVARIANT:
        //  - m_board.size() == m_width
        //  - for (const auto& column : columns) column.size() <= m_height
        //  - none of the Player values is Player::neither


        //
        // Private helpers:
        //
        std::vector<Player>& get_column_(int col_no);
        std::vector<Player>& get_row_(int col_no);

        /// **PRECONDITION** `col_no` is valid and where the last move
        /// was played.
        void update_winner_and_turn_(int col_no);

        /// Returns whether there is a token at the given position.
        bool is_viable_(int row_no, int col_no);


    };

    }





}