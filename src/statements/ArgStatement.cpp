#include "ArgStatement.hpp"
#include "evaluator/StatementEvaluator.hpp"
#include "evaluator/ExpressionEvaluator.hpp"
#include <utility>

namespace arrow {
    
    ArgStatement::ArgStatement(ArrowStatement arrowStatement) 
      : Statement()
      , m_arrowStatement(std::move(arrowStatement))
    {
    }

    std::string ArgStatement::toString() const
    {
        return m_arrowStatement.toString();
    }

    std::shared_ptr<StatementEvaluator> ArgStatement::getEvaluator() const
    {
        struct ArgStatementEvaluator : StatementEvaluator
        {
            explicit ArgStatementEvaluator(ArgStatement statement)
              : m_statement(std::move(statement))
            {
            }

            void evaluate(Cache & cache) const override
            {
                auto evaluator = m_statement.getExpression()->getEvaluator();
                auto evaluated = evaluator->evaluate(cache);
                if(evaluated.m_descriptor != TypeDescriptor::Int) {
                    throw std::runtime_error("whoops");
                }
                auto const index = std::get<int64_t>(evaluated.m_variantType);
                auto progArg = cache.getProgramArgument(index);
                auto identifier = m_statement.getIdentifier();
                cache.add(identifier, progArg);
            }

          private:
            ArgStatement m_statement;
        };
        return std::make_shared<ArgStatementEvaluator>(*this);
    }

    ArgStatement const & ArgStatement::withToken(Token token) const
    {
        m_arrowStatement.withToken(std::move(token));
        return *this;
    }

    Token ArgStatement::getToken() const
    {
        return m_arrowStatement.getToken();
    }

    std::shared_ptr<Expression> ArgStatement::getExpression() const
    {
        return m_arrowStatement.getExpression();
    }

    Token ArgStatement::getIdentifier() const
    {
        return m_arrowStatement.getIdentifier();
    }

    ArrowStatement ArgStatement::getArrowStatement() const
    {
        return m_arrowStatement;
    }
}