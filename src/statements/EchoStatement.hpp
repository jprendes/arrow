#pragma once

#include "ArrowlessStatement.hpp"
#include <memory>

namespace jasl {
    
    class EchoStatement : public Statement
    {
      public:
        EchoStatement(std::shared_ptr<ArrowlessStatement> statement);
        std::string toString() const override;
        std::shared_ptr<StatementEvaluator> getEvaluator() const override;
      private:
        std::shared_ptr<ArrowlessStatement> m_statement;
    };

}