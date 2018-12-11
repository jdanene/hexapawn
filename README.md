  ## Ensuring correctness 
  - line 10: `TEST_CASE("Make a hexa")`
    - Check that the dimensions are correct and correct player has turn 
    - Initialization check
  - line 18: `TEST_CASE("Is a viable move?")`
    - Check if different moves are viable according to rules of the game
    - Specifically test function `hexapawn.is_viable_p`
    - Initialization check
  - line 29: `TEST_CASE("Is a pawn there?")`
    - Check if the pawns are where they are suppose to be for base 3x3 board
    - Specifically test function `hexapawn.pawn_there_p`
    - Initialization check
  - line 37: `TEST_CASE("Is there a pawn in chessboard 4x4?")`
    - Ensure correct for different size board
    - Repeats previous test for 4x4 board
     - Initialization check
  - line 46: `TEST_CASE("Is there a pawn in chessboard 8x7?")`
    - Ensure correct for different size board
    - Repeats previous test for 8x7 board
    - Initialization check
  - line 55: `TEST_CASE("Is there a pawn in chessboard 3x6?")`
    - Ensure correct for different size board
    - Repeats previous test for 3x6 board
     - Initialization check
  - line 65: `TEST_CASE("Check pawns in chessboard")`
    - Checks if pawn in chessboard
    - Initialization check
  - line 74: `TEST_CASE("Game over: draw")`
    - Checks that sequence of game moves that end in a draw is correct
    - Game Play Check 
  - line 117: `TEST_CASE("Pawn on other side: black winner")`
    - Checks that sequence of game moves that end in a black being the winner when blacks pawn reaches the other side is correct
    - Game Play Check
  - line 266: `TEST_CASE("Pawn on other side: white winner")`
    - Checks that sequence of game moves that end in a white being the winner when white pawn reaches the other side is correct
    - Game Play Check
  - line 336: `TEST_CASE("No Moves for white: Black winner")`
    - Checks that sequence of game moves that end in a black being the winner when white has no viable moves is correct
    - Game Play Check
  - line 407: `TEST_CASE("No Moves for black: White winner")`
    - Checks that sequence of game moves that end in a white being the winner when black has no viable moves is correct
    - Game Play Check
  
  
  

