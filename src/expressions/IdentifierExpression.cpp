/// (c) Ben Jones 2019 - present

#include "IdentifierExpression.hpp"
#include "evaluator/ExpressionEvaluator.hpp"
#include "parser/LanguageException.hpp"
#include <utility>

namespace arrow {

    IdentifierExpression::IdentifierExpression(long const lineNumber) 
      : Expression(lineNumber)
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
                if(m_tok.raw == "true") {
                    return {TypeDescriptor::Bool, true};
                } else if(m_tok.raw == "false") {
                    return {TypeDescriptor::Bool, false};
                } else if(!cache.has(m_tok)) {
                    throw LanguageException("Value for identifier not found", m_tok.lineNumber);
                }
                return cache.get(m_tok);
            }
          private:
            Token m_tok;
        };
        return std::make_shared<IdentifierEvaluator>(m_identifier);
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