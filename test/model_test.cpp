#include <model.h>
#include <controller.h>
#include <view.h>
#include <catch.h>
#include <iostream>


using namespace hexapawn;

TEST_CASE("Make a hexapawn")
{
    Model hexapawn(4, 4);
    CHECK(hexapawn.width() == 4);
    CHECK(hexapawn.height() == 4 );
    CHECK(hexapawn.get_turn() == Player::first);
}

TEST_CASE("Is a viable move?")
{
    Model hexapawn(3,3);
    CHECK(!hexapawn.is_viable_p({2,0}, {1,0}, Player::first));
    CHECK(!hexapawn.is_viable_p({2,1}, {1,0}, Player::first));
    CHECK(!hexapawn.is_viable_p({2,2}, {2,1}, Player::first));
    CHECK(!hexapawn.is_viable_p({0,0}, {0,1}, Player::second));
    CHECK(hexapawn.is_viable_p({2,2}, {2,1}, Player::second));
    CHECK(!hexapawn.is_viable_p({1,1}, {1,2}, Player::second));
}

TEST_CASE("Is a pawn there?")
{
    Model hexapawn(3,3);
    CHECK(hexapawn.pawn_there_p({1,2}));
    CHECK(hexapawn.pawn_there_p({2,2}));
    CHECK_THROWS_AS(hexapawn.pawn_there_p({3,0}), ge211::Client_logic_error);
}

TEST_CASE("Is there a pawn in hexapawn 4x4?")
{
    Model hexapawn(4,4);
    CHECK(!hexapawn.pawn_there_p({1,2}));
    CHECK(hexapawn.pawn_there_p({1,0}));
    CHECK(hexapawn.pawn_there_p({3,3}));
    CHECK_THROWS_AS(hexapawn.pawn_there_p({4,0}), ge211::Client_logic_error);
}

TEST_CASE("Is there a pawn in hexapawn 8x7?")
{
    Model hexapawn(8,7);
    CHECK(!hexapawn.pawn_there_p({7,2}));
    CHECK(hexapawn.pawn_there_p({6,0}));
    CHECK(!hexapawn.pawn_there_p({3,3}));
    CHECK_THROWS_AS(hexapawn.pawn_there_p({8,0}), ge211::Client_logic_error);
}

TEST_CASE("Is there a pawn in hexapawn 3x6?")
{
    Model hexapawn(3,6);
    CHECK(hexapawn.pawn_there_p({2,5}));
    CHECK(hexapawn.pawn_there_p({1,5}));
    CHECK(!hexapawn.pawn_there_p({0,3}));
    CHECK_THROWS_AS(hexapawn.pawn_there_p({6,0}), ge211::Client_logic_error);
}

//Ensure that the bottom row corresponds to P1 and top row to P2
TEST_CASE("Check pawns in chessboard")
{
    Model hexapawn(8,8);
    CHECK(hexapawn.get_ele({0,0}) == Player::first);
    CHECK(hexapawn.get_ele({7,7}) == Player::second);
    CHECK_THROWS_AS(hexapawn.get_ele({8,8}), ge211::Client_logic_error);


}


TEST_CASE("Game over: draw")
{
    /* Below is the logical board that we will test: PLAYER1
 *         0   1   2
 *
 *     0  | W| - | W |
 *     1  | -| W | - |
 *     2  | B| B | B |
 *   PLAYER1: {1,0} => {1,1}
 * */
    Model hexapawn(3,3);
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({1,0}) == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::neither);
    CHECK(hexapawn.is_viable_p({1,0},{1,1}, Player::first));
    hexapawn.place_pawn({1,0},{1,1});
    CHECK(hexapawn.get_ele({1,0}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(!hexapawn.game_over_p());
    

    /* Below is the logical board that we will test
     *         0   1   2
     *
     *     0  | W| - | W |
     *     1  | -| B | - |
     *     2  | B| B | - |
     * PLAYER2: {2,2} => {1,1}
     */
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({2,2}) == Player::second);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.is_viable_p({2,2},{1,1}, Player::second));
    hexapawn.place_pawn({2,2},{1,1});
    CHECK(hexapawn.get_ele({2,2}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::second);
    CHECK(!hexapawn.game_over_p());


    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | -| - | W |
     *     1  | -| W | - |
     *     2  | B| B | - |
     *  Player1: {0,0} => {1,1}
     *****/
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({0,0}) == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::second);
    CHECK(hexapawn.is_viable_p({0,0},{1,1}, Player::first));
    hexapawn.place_pawn({0,0},{1,1});
    CHECK(hexapawn.get_ele({0,0}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(!hexapawn.game_over_p());


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
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({0,2}) == Player::second);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.is_viable_p({0,2},{1,1}, Player::second));
    hexapawn.place_pawn({0,2},{1,1});
    CHECK(hexapawn.get_ele({0,2}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::second);
    CHECK(!hexapawn.game_over_p());


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
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({2,0}) == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::second);
    CHECK(hexapawn.is_viable_p({2,0},{1,1}, Player::first));
    hexapawn.place_pawn({2,0},{1,1});
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_ele({2,0}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.game_over_p() );
    CHECK(hexapawn.game_winner() == Player::neither);

}

TEST_CASE("Pawn on other side: black winner")
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
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({1,0}) == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::neither);
    CHECK(hexapawn.is_viable_p({1,0},{1,1}, Player::first));
    hexapawn.place_pawn({1,0},{1,1});
    CHECK(hexapawn.get_ele({1,0}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(!hexapawn.game_over_p());


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
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({0,2}) == Player::second);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.is_viable_p({0,2},{1,1}, Player::second));
    hexapawn.place_pawn({0,2},{1,1});
    CHECK(hexapawn.get_ele({0,2}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::second);
    CHECK(!hexapawn.game_over_p());


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
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({0,0}) == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::second);
    CHECK(hexapawn.is_viable_p({0,0},{1,1}, Player::first));
    hexapawn.place_pawn({0,0},{1,1});
    CHECK(hexapawn.get_ele({0,0}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(!hexapawn.game_over_p());


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
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.get_ele({1,0}) == Player::neither);
    CHECK(hexapawn.is_viable_p({1,1},{1,0}, Player::second));
    hexapawn.place_pawn({1,1},{1,0});
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_ele({1,1}) == Player::neither);
    CHECK(hexapawn.get_ele({1,0}) == Player::second);
    CHECK(hexapawn.game_over_p());
    CHECK(hexapawn.game_winner() == Player::second);
}


TEST_CASE("Pawn on other side: white winner")
{
    Model hexapawn(3,3);

    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | w| w | - |
     *     1  | -| - | w |
     *     2  | B| B | B |
     * */
    /// PLAYER1: {2,0} => {2,1}
    hexapawn.place_pawn({2,0},{2,1});
    hexapawn.update_winner_and_turn();

    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | w| w | - |
     *     1  | -| B | w |
     *     2  | B| - | B |
     * */
    /// PLAYER2: {1,2} => {1,1}
    hexapawn.place_pawn({1,2},{1,1});
    hexapawn.update_winner_and_turn();

    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | -| w | - |
     *     1  | -| w | w |
     *     2  | B| - | B |
     * */
    /// PLAYER1: {0,0} => {1,1}
    hexapawn.place_pawn({0,0},{1,1});
    hexapawn.update_winner_and_turn();


    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | -| w | - |
     *     1  | B| w | w |
     *     2  | -| - | B |
     * */
    /// PLAYER2: {0,2} => {0,1}
    hexapawn.place_pawn({0,2},{0,1});
    hexapawn.update_winner_and_turn();



    /* Below is the logical board that we will test: PLAYER1
     *         0   1   2
     *
     *     0  | -| w | - |
     *     1  | B| - | w |
     *     2  | -| w | B |
     * */
    /// PLAYER1: {1,1} => {1,2}
    hexapawn.place_pawn({1,1},{1,2});
    hexapawn.update_winner_and_turn();

    //Game over P1 on the otherside
    CHECK(hexapawn.game_over_p());
    CHECK(hexapawn.game_winner() == Player::first);

}



TEST_CASE("No Moves for white: Black winner")
{
    Model hexapawn(3,3);
    /* Below is the logical board that we will test: PLAYER1
    *         0   1   2
    *
    *     0  | w| w | - |
    *     1  | -| - | w |
    *     2  | B| B | B |
    *   PLAYER1: {2,0} => {2,1}
    * */

    /// P1: {2,0} => {2,1}
    hexapawn.place_pawn({2,0},{2,1});
    hexapawn.update_winner_and_turn();

    /* Below is the logical board that we will test: PLAYER1
    *         0   1   2
    *
    *     0  | w| w | - |
    *     1  | -| - | B |
    *     2  | B| - | B |
    *   PLAYER2: {1,2} => {2,1}
    * */
    /// P2: {1,2} => {2,1}
    hexapawn.place_pawn({1,2},{2,1});
    hexapawn.update_winner_and_turn();

    /* Below is the logical board that we will test: PLAYER1
    *         0   1   2
    *
    *     0  | w| - | - |
    *     1  | -| w | B |
    *     2  | B| - | B |
    *   PLAYER1: {1,0} => {1,1}
    * */
    /// P1: {1,0} => {1,1}
    hexapawn.place_pawn({1,0},{1,1});
    hexapawn.update_winner_and_turn();

    /* Below is the logical board that we will test: PLAYER1
    *         0   1   2
    *
    *     0  | w| - | - |
    *     1  | -| B | B |
    *     2  | B| - | - |
    *   PLAYER2: {2,2} => {1,1}
    * */
    /// P2: {2,2} => {1,1}
    hexapawn.place_pawn({2,2},{1,1});
    hexapawn.update_winner_and_turn();

    /* Below is the logical board that we will test: PLAYER1
    *         0   1   2
    *
    *     0  | -| - | - |
    *     1  | w| B | B |
    *     2  | B| - | - |
    *   PLAYER1: {0,0} => {0,1}
    * */
    /// P2: {0,0} => {0,1}
    hexapawn.place_pawn({0,0},{0,1});
    hexapawn.update_winner_and_turn();

    //Game over black wins since white can not move
    CHECK(hexapawn.game_over_p());
    CHECK(hexapawn.game_winner() == Player::second);
}

TEST_CASE("No Moves for black: White winner")
{
    Model hexapawn(4,4);

    /// Step1: P1: {2,0} => {2,1}
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({2,0}) == Player::first);
    CHECK(hexapawn.get_ele({2,1}) == Player::neither);
    CHECK(hexapawn.is_viable_p({2,0},{2,1}, Player::first) == true);
    hexapawn.place_pawn({2,0},{2,1});
    CHECK(hexapawn.get_ele({2,0}) == Player::neither);
    CHECK(hexapawn.get_ele({2,1}) == Player::first);
    CHECK(hexapawn.game_over_p() == false);

    /// Step2: P2: {3,3} => {3,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({3,3}) == Player::second);
    CHECK(hexapawn.get_ele({3,2}) == Player::neither);
    CHECK(hexapawn.is_viable_p({3,3},{3,2}, Player::second) == true);
    hexapawn.place_pawn({3,3},{3,2});
    CHECK(hexapawn.get_ele({3,3}) == Player::neither);
    CHECK(hexapawn.get_ele({3,2}) == Player::second);
    CHECK(hexapawn.game_over_p() == false);

    // Step3: P1: {1,0} => {1,1}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({1,0}) == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::neither);
    CHECK(hexapawn.is_viable_p({1,0},{1,1}, Player::first) == true);
    hexapawn.place_pawn({1,0},{1,1});
    CHECK(hexapawn.get_ele({1,0}) == Player::neither);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.game_over_p() == false);

    // Step4: P2: {0,3} => {0,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({0,3}) == Player::second);
    CHECK(hexapawn.get_ele({0,2}) == Player::neither);
    CHECK(hexapawn.is_viable_p({0,3},{0,2}, Player::second) == true);
    hexapawn.place_pawn({0,3},{0,2});
    CHECK(hexapawn.get_ele({0,3}) == Player::neither);
    CHECK(hexapawn.get_ele({0,2}) == Player::second);
    CHECK(hexapawn.game_over_p() == false);

    // Step5: P1: {2,1} => {3,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({2,1}) == Player::first);
    CHECK(hexapawn.get_ele({3,2}) == Player::second);
    CHECK(hexapawn.is_viable_p({2,1},{3,2}, Player::first) == true);
    hexapawn.place_pawn({2,1},{3,2});
    CHECK(hexapawn.get_ele({2,1}) == Player::neither);
    CHECK(hexapawn.get_ele({3,2}) == Player::first);
    CHECK(hexapawn.game_over_p() == false);

    // Sterp6: P2: {1,3} => {1,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({1,3}) == Player::second);
    CHECK(hexapawn.get_ele({1,2}) == Player::neither);
    CHECK(hexapawn.is_viable_p({1,3},{1,2}, Player::second) == true);
    hexapawn.place_pawn({1,3},{1,2});
    CHECK(hexapawn.get_ele({1,3}) == Player::neither);
    CHECK(hexapawn.get_ele({1,2}) == Player::second);
    CHECK(hexapawn.game_over_p() == false);

    // Step7: P1: {1,1} => {0,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({1,1}) == Player::first);
    CHECK(hexapawn.get_ele({0,2}) == Player::second);
    CHECK(hexapawn.is_viable_p({1,1},{0,2}, Player::first) == true);
    hexapawn.place_pawn({1,1},{0,2});
    CHECK(hexapawn.get_ele({1,1}) == Player::neither);
    CHECK(hexapawn.get_ele({0,2}) == Player::first);
    CHECK(hexapawn.game_over_p() == false);

    // Step8: P2: {2,3} => {3,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({2,3}) == Player::second);
    CHECK(hexapawn.get_ele({3,2}) == Player::first);
    CHECK(hexapawn.is_viable_p({2,3},{3,2}, Player::second) == true);
    hexapawn.place_pawn({2,3},{3,2});
    CHECK(hexapawn.get_ele({2,3}) == Player::neither);
    CHECK(hexapawn.get_ele({3,2}) == Player::second);
    CHECK(hexapawn.game_over_p() == false);

    // Step9: P1: {0,0} => {0,1}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({0,0}) == Player::first);
    CHECK(hexapawn.get_ele({0,1}) == Player::neither);
    CHECK(hexapawn.is_viable_p({0,0},{0,1}, Player::first) == true);
    hexapawn.place_pawn({0,0},{0,1});
    CHECK(hexapawn.get_ele({0,0}) == Player::neither);
    CHECK(hexapawn.get_ele({0,1}) == Player::first);
    CHECK(hexapawn.game_over_p() == false);

    // Step10: P2: {3,2} => {3,1}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::second);
    CHECK(hexapawn.get_ele({3,2}) == Player::second);
    CHECK(hexapawn.get_ele({3,1}) == Player::neither);
    CHECK(hexapawn.is_viable_p({3,2},{3,1}, Player::second) == true);
    hexapawn.place_pawn({3,2},{3,1});
    CHECK(hexapawn.get_ele({3,2}) == Player::neither);
    CHECK(hexapawn.get_ele({3,1}) == Player::second);
    CHECK(hexapawn.game_over_p() == false);

    // Step11: P1: {0,1} => {1,2}
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.get_turn() == Player::first);
    CHECK(hexapawn.get_ele({0,1}) == Player::first);
    CHECK(hexapawn.get_ele({1,2}) == Player::second);
    CHECK(hexapawn.is_viable_p({0,1},{1,2}, Player::first) == true);
    hexapawn.place_pawn({0,1},{1,2});
    CHECK(hexapawn.get_ele({0,1}) == Player::neither);
    CHECK(hexapawn.get_ele({1,2}) == Player::first);
    CHECK(hexapawn.game_over_p() == false);

    // black has no moves, white wins
    hexapawn.update_winner_and_turn();
    CHECK(hexapawn.game_over_p() == true);
    CHECK(hexapawn.game_winner() == Player::first);

}