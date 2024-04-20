#include "Calculator.h"
#include <string>
#include "Variable.h"
#include "Function.h"
#include <variant>
#include <vector>
#include <iostream>

//double Calculator::CalculateFn(std::variant<double*, Function*> f)
//{
//    if (((std::holds_alternative<Function*>(f) && std::get<Function*>(f)->GetFirstIdValue() != nullptr) ||
//        (std::holds_alternative<double*>(f) && std::get<double*>(f) != nullptr))
//        &&
//        ((std::holds_alternative<Function*>(f) && std::get<Function*>(f) != nullptr) ||
//            (std::holds_alternative<double*>(f) && std::get<double*>(f) != nullptr)))
//    {
//        if (std::holds_alternative<Function*>(f))
//        {
//            // �������� �������� ������� � ������� ����������
//            auto firstId = (std::get<Function*>(f))->GetFirstIdValue();
//            auto secondId = (std::get<Function*>(f))->GetSecondIdValue();
//            // ���������, �� �������� �� ��������� �������
//            if (std::holds_alternative<double*>(firstId) && std::holds_alternative<double*>(secondId))
//            {
//                // ��� ��������� - �����
//                double val1 = *std::get<double*>(firstId);
//                double val2 = *std::get<double*>(secondId);
//                // ���������� ��������� � ����������� �� ���������
//                return (std::get<Function*>(f))->GetOperator() == '*' ? val1 * val2 :
//                    (std::get<Function*>(f))->GetOperator() == '+' ? val1 + val2 :
//                    (std::get<Function*>(f))->GetOperator() == '-' ? val1 - val2 :
//                    val1 / val2;
//            }
//            else if (std::holds_alternative<Function*>(firstId) && std::holds_alternative<Function*>(secondId))
//            {
//                // ��� ��������� - �������, ���������� �������� CalculateFn ��� ������� �� ���
//                double val1 = CalculateFn(std::get<Function*>(firstId));
//                double val2 = CalculateFn(std::get<Function*>(secondId));
//                // ���������� ��������� � ����������� �� ���������
//                return (std::get<Function*>(f))->GetOperator() == '*' ? val1 * val2 :
//                    (std::get<Function*>(f))->GetOperator() == '+' ? val1 + val2 :
//                    (std::get<Function*>(f))->GetOperator() == '-' ? val1 - val2 :
//                    val1 / val2;
//            }
//            else
//            {
//                // ��������� ������ ����� ����������: ������������� ������ �� ��� � ������������� �������
//                if (std::holds_alternative<Function*>(firstId))
//                {
//                    // ���������� ������ ������ ��������
//                    double val1 = CalculateFn(std::get<Function*>(firstId));
//                    double val2 = *std::get<double*>(secondId);
//                    // ���������� ��������� � ����������� �� ���������
//                    return (std::get<Function*>(f))->GetOperator() == '*' ? val1 * val2 :
//                        (std::get<Function*>(f))->GetOperator() == '+' ? val1 + val2 :
//                        (std::get<Function*>(f))->GetOperator() == '-' ? val1 - val2 :
//                        val1 / val2;
//                }
//                else if (std::holds_alternative<Function*>(secondId))
//                {
//                    // ���������� ������ ������ ��������
//                    double val1 = *std::get<double*>(firstId);
//                    double val2 = CalculateFn(std::get<Function*>(secondId));
//                    // ���������� ��������� � ����������� �� ���������
//                    return (std::get<Function*>(f))->GetOperator() == '*' ? val1 * val2 :
//                        (std::get<Function*>(f))->GetOperator() == '+' ? val1 + val2 :
//                        (std::get<Function*>(f))->GetOperator() == '-' ? val1 - val2 :
//                        val1 / val2;
//                }
//            }
//        }
//    }
//
//	//return m_firstId == nullptr ? NAN : *m_firstId;
//}


double Calculator::Operate(double val1, double val2, char op)
{
    switch (op)
    {
    case '*':
        return val1 * val2;
    case '+':
        return val1 + val2;
    case '-':
        return val1 - val2;
    case '/':
        return val1 / val2;
    default:
        return val1;
    }
}

double Calculator::CalculateFn(std::variant<Variable*, Function*> f)
{
    //���� double 
    if (std::holds_alternative<Variable*>(f))
    {
        if (std::get<Variable*>(f) == nullptr)
        {
            return NAN;
        }
        return std::get<Variable*>(f)->GetValue();
    }
    
    //���� Function
    Function* fn = std::get<Function*>(f);
    std::variant<Variable*, Function*> firstId = fn->GetFirstIdValue();
    std::variant<Variable*, Function*> secondId = fn->GetSecondIdValue();

    double val1 = CalculateFn(firstId);
    double val2 = CalculateFn(secondId);

    return Operate(val1, val2, fn->GetOperator());
}


double Calculator::Calculate(std::string idName)
{
    for (auto& f : fns)
    {
        if (idName == f.GetName())
        {
            std::variant<Variable*, Function*> firstId = f.GetFirstIdValue();
            std::variant<Variable*, Function*> secondId = f.GetSecondIdValue();
            double val1 = CalculateFn(firstId);
            double val2 = CalculateFn(secondId);

            return Operate(val1, val2, f.GetOperator());
            //return CalculateFn(&tempFunction);
        }
    }

    if (vars.find(idName) != vars.end())
    {
        return vars[idName].GetValue();
    }

    throw std::invalid_argument("Unknown id!");
}