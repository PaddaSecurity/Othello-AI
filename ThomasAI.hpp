//ThomasAI.hpp

#ifndef THOMAS_HPP
#define THOMAS_HPP

#include "OthelloAI.hpp"
#include <vector>


namespace tcistull
{
    class ThomasAI : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
        std::vector<std::pair<int, int>> findAllMoves(std::unique_ptr<OthelloGameState>& state);
        unsigned search(std::unique_ptr<OthelloGameState>& state, unsigned depth);

    private:
        char turn;
    };
}


#endif