#include <model.h>
#include <controller.h>
#include <view.h>
#include <catch.h>
#include <iostream>


using namespace hexapawn;

TEST_CASE("Make a chessboard")
{
    Model hexapawn(4, 4);
    CHECK(hexapawn.width() == 4);
    CHECK(hexapawn.height() == 4 );
    CHECK(hexapawn.get_turn() == Player::first);
}

TEST_CASE("Is a viable move?")
{
    Model hexapawn(3,3);
    CHECK(hexapawn.is_viable_p({2,0}, {1,0}, Player::first) == false);
    CHECK(hexapawn.is_viable_p({2,1}, {1,0}, Player::first) == false);
    CHECK(hexapawn.is_viable_p({2,2}, {2,1}, Player::first) == false);
    CHECK(hexapawn.is_viable_p({0,0}, {0,1}, Player::second) == false);
    CHECK(hexapawn.is_viable_p({2,2}, {2,1}, Player::second) == true);
    CHECK(hexapawn.is_viable_p({1,1}, {1,2}, Player::second) == false);
}

TEST_CASE("Is a pawn allowed?")
{
    Model hexapawn(3,3);
    CHECK(hexapawn.pawn_there_p({1,2}) == true);
    CHECK(hexapawn.pawn_there_p({2,2}) == true);
    CHECK_THROWS_AS(hexapawn.pawn_there_p({3,0}), ge211::Client_logic_error);
}

TEST_CASE("Is there a pawn in chessboard?")
{
    Model hexapawn(4,4);
    CHECK(hexapawn.pawn_there_p({1,2}) == false);
    CHECK(hexapawn.pawn_there_p({1,0}) == true);
    CHECK(hexapawn.pawn_there_p({3,3}) == true);
    CHECK_THROWS_AS(hexapawn.pawn_there_p({4,0}), ge211::Client_logic_error);
}


//Ensure that the bottom row corresponds to P1 and top row to P2
TEST_CASE("Check pawns in chessboard")
{
    Model hexapawn(8,8);
    CHECK(hexapawn.get_ele({0,0}) == Player::first);

}


TEST_CASE("Game over: draw")
{
    Model hexapawn(3,3);

    std::cout << "Test: Game over due to draw." << "\n";

    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | W| - | W |
     *     1  | -| W | - |
     *     2  | B| B | B |
     *   PLAYER1: {1,0} => {1,1}
     * */
    /// P1: {1,0} => {1,1}
    std::cout << "\n";
    std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
    std::cout << "Before move "<< "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,0})) << "\n";
    std::cout << "Element {1,2} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Viable? {1,2} =>  {1,1} is: "<< hexapawn.is_viable_p({1,0},{1,1},hexapawn.get_turn())<< "\n";
    hexapawn.place_pawn({1,0},{1,1});
    std::cout << "After move "<< "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,0})) << "\n";
    std::cout << "Element {1,2} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";

    /* Below is the logical board that we will test
     *         0   1   2
     *
     *     0  | W| - | W |
     *     1  | -| B | - |
     *     2  | B| B | - |
     * PLAYER2: {2,2} => {1,1}
     */
     /// [Update Turn: P1 => P2] AND [Check if winner: No winner => No winner]
     hexapawn.update_winner_and_turn();
     std::cout << "\n";
     std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
     std::cout << "Before move "<< "\n";
     std::cout << "Element {0,0} is: "<< as_integer(hexapawn.get_ele({2,2})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     hexapawn.place_pawn({2,2},{1,1});
     std::cout << "After move "<< "\n";
     std::cout << "Element {0,0} is: "<< as_integer(hexapawn.get_ele({2,2})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";

//    /* Below is the logical board that we will test: PLAYER1
//     *         0   1   2
//     *
//     *     0  | -| - | W |
//     *     1  | -| W | - |
//     *     2  | B| B | - |
//     *  Player1: {0,0} => {1,1}
//     *****/
//
     hexapawn.update_winner_and_turn();
     std::cout << "\n";
     std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
     std::cout << "Before move "<< "\n";
     std::cout << "Element {2,2} is: "<< as_integer(hexapawn.get_ele({0,0})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     hexapawn.place_pawn({0,0},{1,1});
     std::cout << "After move "<< "\n";
     std::cout << "Element {2,2} is: "<< as_integer(hexapawn.get_ele({0,0})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";

//    /* Below is the logical board that we will test:
//     *         0   1   2
//     *
//     *     0  | -| - | W |
//     *     1  | -| B | - |
//     *     2  | -| B | - |
//     *  - Player 2: {0,2}=> {1,1}
//     *****/
//
     hexapawn.update_winner_and_turn();
     std::cout << "\n";
     std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
     std::cout << "Before move "<< "\n";
     std::cout << "Element {0,2} is: "<< as_integer(hexapawn.get_ele({0,2})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     hexapawn.place_pawn({0,2},{1,1});
     std::cout << "After move "<< "\n";
     std::cout << "Element {2,0} is: "<< as_integer(hexapawn.get_ele({0,2})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";
     std::cout << "Game winner? : "<< as_integer(hexapawn.game_winner()) << "\n";

//    /* Below is the logical board that we will test:
//     *         0   1   2
//     *
//     *     0  | -| - | - |
//     *     1  | -| w | - |
//     *     2  | -| B | - |
//     *  - Player 1: {2,0}=> {1,1}
//     *  - Draw
//     *****/
//
     hexapawn.update_winner_and_turn();
     std::cout << "\n";
     std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
     std::cout << "Before move "<< "\n";
     std::cout << "Element {2,0} is: "<< as_integer(hexapawn.get_ele({2,0})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
     hexapawn.place_pawn({2,0},{1,1});
     std::cout << "After move "<< "\n";
     std::cout << "Element {2,0} is: "<< as_integer(hexapawn.get_ele({2,0})) << "\n";
     std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    //End in a draw good!
     hexapawn.update_winner_and_turn();
     std::cout << "New Player turn is: "<< as_integer(hexapawn.get_turn()) << "\n";
     std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";
     std::cout << "Game winner? : "<< as_integer(hexapawn.game_winner()) << "\n";
     std::cout << "\n";
     std::cout << "\n";
}


TEST_CASE("Game over: winner")
{
    Model hexapawn(3,3);

    std::cout << "Test: Game over due to winner." << "\n";

    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | w| - | w |
     *     1  | -| w | - |
     *     2  | B| B | B |
     *   PLAYER1: {1,0} => {1,1}
     * */
    /// P1: {1,0} => {1,1}
    std::cout << "\n";
    std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
    std::cout << "Before move "<< "\n";
    std::cout << "Element {1,0} is: "<< as_integer(hexapawn.get_ele({1,0})) << "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Viable? {1,2} =>  {1,1} is: "<< hexapawn.is_viable_p({1,2},{1,1},hexapawn.get_turn())<< "\n";
    hexapawn.place_pawn({1,0},{1,1});
    std::cout << "After move "<< "\n";
    std::cout << "Element {1,0} is: "<< as_integer(hexapawn.get_ele({1,0})) << "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";

    /* Below is the logical board that we will test
     *         0   1   2
     *
     *     0  | W| - | W |
     *     1  | -| B | - |
     *     2  | -| B | B |
     * PLAYER2: {0,2} => {1,1}
     */
    /// [Update Turn: P1 => P2] AND [Check if winner: No winner => No winner]
    /// P2: {0,2} => {1,1}
    hexapawn.update_winner_and_turn();
    std::cout << "\n";
    std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
    std::cout << "Before move "<< "\n";
    std::cout << "Element {0,2} is: "<< as_integer(hexapawn.get_ele({0,2})) << "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    hexapawn.place_pawn({0,2},{1,1});
    std::cout << "After move "<< "\n";
    std::cout << "Element {0,0} is: "<< as_integer(hexapawn.get_ele({0,2})) << "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";

//    /* Below is the logical board that we will test: PLAYER1
//     *         0   1   2
//     *
//     *     0  | -| - | W |
//     *     1  | W| B | - |
//     *     2  | -| B | B |
//     *  Player1: {0,0} => {0,1}
//     *****/
//
    hexapawn.update_winner_and_turn();
    std::cout << "\n";
    std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
    std::cout << "Before move "<< "\n";
    std::cout << "Element {0,0} is: "<< as_integer(hexapawn.get_ele({0,0})) << "\n";
    std::cout << "Element {0,1} is: "<< as_integer(hexapawn.get_ele({0,1})) << "\n";
    hexapawn.place_pawn({0,0},{0,1});
    std::cout << "After move "<< "\n";
    std::cout << "Element {0,0} is: "<< as_integer(hexapawn.get_ele({0,0})) << "\n";
    std::cout << "Element {0,1} is: "<< as_integer(hexapawn.get_ele({0,1})) << "\n";
    std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";

//    /* Below is the logical board that we will test:
//     *         0   1   2
//     *
//     *     0  | -| B | W |
//     *     1  | W| - | - |
//     *     2  | -| B | B |
//     *  - Player 2: {1,1}=> {1,0}
//     *****/
//
    hexapawn.update_winner_and_turn();
    std::cout << "\n";
    std::cout << "Who's turn: "<< as_integer(hexapawn.get_turn()) << "\n";
    std::cout << "Before move "<< "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Element {1,0} is: "<< as_integer(hexapawn.get_ele({1,0})) << "\n";
    hexapawn.place_pawn({1,1},{1,0});
    hexapawn.update_winner_and_turn();
    std::cout << "After move "<< "\n";
    std::cout << "Element {1,1} is: "<< as_integer(hexapawn.get_ele({1,1})) << "\n";
    std::cout << "Element {1,0} is: "<< as_integer(hexapawn.get_ele({1,0})) << "\n";
    std::cout << "Game over? : "<< hexapawn.game_over_p() << "\n";
    std::cout << "Game winner? : "<< as_integer(hexapawn.game_winner()) << "\n";

}
