#pragma once

#include "ExpressionEvaluator.hpp"
#include "expressions/BooleanExpression.hpp"
#include "representation/Type.hpp"

namespace jasl {

    class BooleanExpression;
    class BooleanExpressionEvaluator : public ExpressionEvaluator
    {
      public:
        BooleanExpressionEvaluator(BooleanExpression expression);
        Type evaluate(Cache&) const override;
      private:
        BooleanExpression m_expression;
    };

}