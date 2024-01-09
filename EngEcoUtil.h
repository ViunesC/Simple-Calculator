//
// Created by Re_Innocence on 2023/12/17.
//

#ifndef REVIEWCPP_ENGECOUTIL_H
#define REVIEWCPP_ENGECOUTIL_H


class EngEcoUtil {
public:
    EngEcoUtil();
    double SLD(double purchase_price, double salvage_value, int useful_life, int Nperiod);
    double DBD(double depreciation_rate, double market_value, int Nperiod);
    double PF(double present_value, double future_value, double interest, int num_period);
    double PA(double present_value, double annuity, double interest, int num_period);
    double AF(double future_value, double annuity, double interest, int num_period);
    double CRF(double capital_cost, double salvage_value, double interest, int num_period);
    double AGF(double value_increased, double interest, int num_period);
    double GGF(double rate_growth, double interest, int num_period);
    double IRR(double target_coef, double interest1, double interest2, double coef1, double coef2);
};


#endif //REVIEWCPP_ENGECOUTIL_H
