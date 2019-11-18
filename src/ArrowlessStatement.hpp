#pragma once

#include "Node.hpp"
#include "Statement.hpp"
#include "Token.hpp"
#include "Expression.hpp"
#include <memory>
#include <utility>

namespace jasl {
    
    class ArrowlessStatement : public Statement
    {
      public:
        ArrowlessStatement() : Statement() {}
        ArrowlessStatement & withToken(Token token)
        {
            m_keywordToken = std::move(token);
            return *this;
        }
        ArrowlessStatement & withExpression(std::shared_ptr<Expression> expression)
        {
            m_expression = std::move(expression);
            return *this;
        }

        std::string toString() const override
        {
            std::string str("Keyword: ");
            str.append(m_keywordToken.raw);
            str.append("\nExpression: ");
            str.append(m_expression->toString());
            return str;
        }

        Token m_keywordToken; // the int keywork
        std::shared_ptr<Expression> m_expression;
    };

}