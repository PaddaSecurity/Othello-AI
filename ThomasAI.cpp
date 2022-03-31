// ThomasAI.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include "ThomasAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, tcistull::ThomasAI, "THOMAS AI");


std::pair<int, int> tcistull::ThomasAI::chooseMove(const OthelloGameState& state)
{
    std::pair<int, int> bestMove;
    std::vector<std::pair<int, int>> allPossibleMoves;
    
    unsigned highestScore = 0;

    if (state.isBlackTurn()) { turn = 'B'; } else { turn = 'W'; }

    std::unique_ptr<OthelloGameState> tempCopy = state.clone();
    allPossibleMoves = findAllMoves(tempCopy);

    bestMove.first = allPossibleMoves[0].first;
    bestMove.second = allPossibleMoves[0].second;

    for (unsigned i = 0; i < allPossibleMoves.size(); ++i)
    {
        unsigned currScore;
        std::unique_ptr<OthelloGameState> copyOfBoard = state.clone();
        if (copyOfBoard->isValidMove(allPossibleMoves[i].first, allPossibleMoves[i].second))
        {
            copyOfBoard->makeMove(allPossibleMoves[i].first, allPossibleMoves[i].second);
        }
        
        currScore = search(copyOfBoard, 2);
        
        if (currScore > highestScore)
        {
            highestScore = currScore;
            bestMove = allPossibleMoves[i];
        }
    }
    return bestMove;
}

std::vector<std::pair<int, int>> tcistull::ThomasAI::findAllMoves(std::unique_ptr<OthelloGameState>& state)
{
    std::vector<std::pair<int, int>> allMoves;

    for (unsigned x = 0; x < state->board().width(); ++x)
    {
        for (unsigned y = 0; y < state->board().height(); ++y)
        {
            if (state->isValidMove(x,y))
            {
                allMoves.push_back(std::pair<int, int> (x,y));
            }
        }
    }
    
    return allMoves;
}

unsigned tcistull::ThomasAI::search(std::unique_ptr<OthelloGameState>& state, unsigned depth)
{
    int newScore = 0;
    unsigned bestScore = 0;
    int lowestScore = 1000;
    std::vector<std::pair<int, int>> newPossibleMoves = tcistull::ThomasAI::findAllMoves(state);
    
    if (depth == 0)
    {
        if (state->isBlackTurn())
        {
            return state->blackScore() - state->whiteScore();
        }
        return state->whiteScore() - state->blackScore();
    }
    else
    {
        if (turn == 'B' || turn == 'W')
        {
            if (state->isBlackTurn() || state->isWhiteTurn())
            {
                for (unsigned i = 0; i < newPossibleMoves.size(); ++i)
                {
                    std::unique_ptr<OthelloGameState> newCopy = state->clone();
                    if (newCopy->isValidMove(newPossibleMoves[i].first, newPossibleMoves[i].second))
                    {
                        newCopy->makeMove(newPossibleMoves[i].first, newPossibleMoves[i].second);
                        newScore += newCopy->isBlackTurn() ? newCopy->blackScore() : newCopy->whiteScore();
                        search(newCopy, depth - 1);
                        
                        if (newScore > bestScore)
                        {
                            bestScore = newScore;
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            for (unsigned i = 0; i < newPossibleMoves.size(); ++i)
                {
                    std::unique_ptr<OthelloGameState> newCopy = state->clone();
                    if (newCopy->isValidMove(newPossibleMoves[i].first, newPossibleMoves[i].second))
                    {
                        newCopy->makeMove(newPossibleMoves[i].first, newPossibleMoves[i].second);
                        newScore += newCopy->isBlackTurn() ? newCopy->blackScore() : newCopy->whiteScore();
                        search(newCopy, depth - 1);
                    
                        if (newScore < lowestScore)
                        {
                            lowestScore = newScore;
                        }
                    }
                }
            return lowestScore;
        }
    }
    return 1;
}