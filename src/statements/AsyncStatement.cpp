/// (c) Ben Jones 2019 - present

#include "AsyncStatement.hpp"
#include "evaluator/StatementEvaluator.hpp"
#include "utility/ThreadManager.hpp"
#include <utility>

namespace arrow {
    AsyncStatement::AsyncStatement(long const lineNumber,
                                   std::ostream & os)
    : Statement(lineNumber, os)
    {
    }
    AsyncStatement & AsyncStatement::withToken(Token token)
    {
        m_keywordToken = std::move(token);
        return *this;
    }
    void AsyncStatement::addBodyStatement(std::shared_ptr<Statement> bodyStatement)
    {
        m_bodyStatements.emplace_back(std::move(bodyStatement));
    }

    std::vector<std::shared_ptr<Statement>>
    AsyncStatement::getBodyStatements() const
    {
        return m_bodyStatements;
    }

    std::string AsyncStatement::toString() const
    {
        return ""; // todo
    }

    std::shared_ptr<StatementEvaluator> AsyncStatement::getEvaluator() const
    {

        struct AsyncStatementEvaluator : public StatementEvaluator
        {
            explicit AsyncStatementEvaluator(AsyncStatement statement)
              : m_statement(std::move(statement))
            {
            }

           StatementResult evaluate(Cache & cache) const override
            {
                auto const bodyStatements = m_statement.getBodyStatements();
                ThreadManager::create([bodyStatements{std::move(bodyStatements)}, &cache] {
                    for(auto const & inner : bodyStatements) {
                        inner->getEvaluator()->evaluate(cache);
                    }
                });
                return StatementResult::Continue;
            }
          private:
            AsyncStatement m_statement;
        };

        return std::make_shared<AsyncStatementEvaluator>(*this);
    }
}