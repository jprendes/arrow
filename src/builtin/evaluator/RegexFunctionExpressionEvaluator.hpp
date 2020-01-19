/// (c) Ben Jones 2019

#pragma once

#include "expressions/evaluator/ExpressionEvaluator.hpp"
#include "builtin/RegexFunctionExpression.hpp"
#include "representation/Cache.hpp"

namespace arrow {
    class RegexFunctionExpressionEvaluator : public ExpressionEvaluator
    {
      public:
        explicit RegexFunctionExpressionEvaluator(RegexFunctionExpression expression);
        Type evaluate(Cache&) const override;
      private:
        RegexFunctionExpression m_expression;
    };
}