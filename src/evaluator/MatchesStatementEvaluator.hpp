#pragma once

#include "StatementEvaluator.hpp"
#include "statements/MatchesStatement.hpp"
#include "representation/Type.hpp"
#include "representation/Cache.hpp"
#include <memory>

namespace arrow {

    class MatchesStatementEvaluator : public StatementEvaluator
    {
      public:
        explicit MatchesStatementEvaluator(MatchesStatement statement);
        void evaluate(Cache&) const override;
      private:
        MatchesStatement m_statement;
    };
}