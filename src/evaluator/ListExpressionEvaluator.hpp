#pragma once

#include "ExpressionEvaluator.hpp"
#include "expressions/ListExpression.hpp"
#include "representation/Type.hpp"
#include "representation/Cache.hpp"
#include <memory>

namespace jasl {

    class ListExpressionEvaluator : public ExpressionEvaluator
    {
      public:
        explicit ListExpressionEvaluator(ListExpression listExpression);
        Type evaluate(Cache&) const override;
      private:
        ListExpression m_listExpression;
    };
}