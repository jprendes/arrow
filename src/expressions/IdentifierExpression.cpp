#include "IdentifierExpression.hpp"
#include "evaluator/ExpressionEvaluator.hpp"
#include <utility>

namespace jasl {

    IdentifierExpression::IdentifierExpression()
     : Expression()
     , m_identifier()
    {
    }

    std::shared_ptr<ExpressionEvaluator> 
    IdentifierExpression::getEvaluator() const
    {
        struct IdentifierEvaluator : public ExpressionEvaluator {
            IdentifierEvaluator(Token tok) : m_tok(std::move(tok))
            {
            }

            Type evaluate(Cache & cache) const override
            {
                if(!cache.has(m_tok.raw)) {
                    throw std::runtime_error("Value for identifier not found.");
                }
                return cache.get(m_tok.raw);
            }
          private:
            Token m_tok;
        };
        return std::make_shared<IdentifierEvaluator>(m_identifier);
    }

    DecayType IdentifierExpression::decayType() const
    {
        return DecayType::DECAYS_TO_STRING;
    }

    IdentifierExpression & IdentifierExpression::withIdentifierToken(Token identifier)
    {
        m_identifier = std::move(identifier);
        return *this;
    }

    Token IdentifierExpression::getIdentifierToken() const
    {
        return  m_identifier;
    }

    std::string IdentifierExpression::toString() const
    {
        std::string str("\nIdentifier expression: ");
        return str.append(m_identifier.raw);
    }
}