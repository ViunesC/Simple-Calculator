//
// Created by Re_Innocence on 2023/12/17.
//
#include <iostream>
#include <cmath>
#include "EngEcoUtil.h"

EngEcoUtil::EngEcoUtil() = default;

/**
 * Calculate depreciation using straight-line-depreciation(SLD) method
 * @param purchase_price purchase price of asset
 * @param salvage_value salvage value of asset at end of its lifecycle
 * @param useful_life useful life of asset, in years
 * @param Nperiod number of years since the asset being put into use, can be omitted (=-1)
 * @return depreciation in any period if *Nperiod* is omitted, or book value at end of *Nperiod*
 */
double EngEcoUtil::SLD(double purchase_price, double salvage_value, int useful_life, int Nperiod) {
    double depreciation = (purchase_price - salvage_value)/useful_life;
    if (Nperiod == -1)
        return depreciation;
    return purchase_price - Nperiod * depreciation;
}

/**
 * Calculate depreciation using declining-balance-depreciation(DBD) method
 * @param depreciation_rate rate of which asset is depreciated
 * @param market_value purchase value of asset
 * @param Nperiod number of years since the asset being put into use
 * @return Book value at the end of year *Nperiod*
 */
double EngEcoUtil::DBD(double depreciation_rate, double market_value, int Nperiod) {
    return market_value * pow(1-depreciation_rate,Nperiod);
}

/**
 * Calculate Present/Future value using Future/Present value, interest rate and number of periods
 * @param present_value present value, can be omitted (=-1) if future value is filled in
 * @param future_value future value, can be omitted (=-1) if present value is filled in
 * @param interest effective annual interest rate
 * @param num_period number of periods
 * @return Present value if *present_value* is omitted, or future value if *future_value* is omitted
 */
double EngEcoUtil::PF(double present_value, double future_value, double interest, int num_period) {
    if (present_value == -1 && future_value == -1) {
        std::cout << "Invalid argument: Enter at least 1 argument for PF(double,double,int)" << std::endl;
        return -1;
    }

    if (present_value == -1)
        return future_value / pow(1+interest,num_period);
    return present_value * pow(1+interest,num_period);
}

/**
 * Calculate Present value/Annuity using Annuity/Present value, interest rate and number of periods
 * @param present_value present value, can be omitted (=-1) if annuity is filled in
 * @param annuity annuity, can be omitted (=-1) if present value is filled in
 * @param interest effective annual interest rate
 * @param num_period number of periods
 * @return Present value if *present_value* is omitted, or annuity if *annuity* is omitted
 */
double EngEcoUtil::PA(double present_value, double annuity, double interest, int num_period) {
    double factor = pow(1 + interest,num_period);
    if (present_value == -1)
        return annuity * ((factor - 1) / (interest * factor));
    return present_value * (interest * factor / (factor - 1));
}

/**
 * Calculate future value/Annuity using Annuity/future value, interest rate and number of periods
 * @param future_value future value, can be omitted (=-1) if annuity is filled in
 * @param annuity annuity, can be omitted (=-1) if future value is filled in
 * @param interest effective annual interest rate
 * @param num_period number of periods
 * @return Future value if *future_value* is omitted, or annuity if *annuity* is omitted
 */
double EngEcoUtil::AF(double future_value, double annuity, double interest, int num_period) {
    double factor = pow(1 + interest,num_period);
    if (future_value == -1)
        return annuity * ((factor - 1) / interest);
    return future_value * (interest / (factor - 1));
}

/**
 * Calculate capital recovery of asset using capital cost, salvage value, interest rate and number of periods
 * @param capital_cost capital cost or first cost
 * @param salvage_value salvage value at end of asset's lifecycle
 * @param interest effective annual interest rate
 * @param num_period useful life of asset, in years
 * @return capital recovery of asset
 */
double EngEcoUtil::CRF(double capital_cost, double salvage_value, double interest, int num_period) {
    return PA(capital_cost - salvage_value, -1, interest, num_period) + salvage_value * interest;
}

/**
 * Calculate conversion factor for arithmetic gradient series of present worth
 * @param value_increased value increased per period, constant
 * @param interest effective annual interest rate
 * @param num_period number of periods
 * @return conversion factor for arithmetic gradient series
 */
double EngEcoUtil::AGF(double value_increased, double interest, int num_period) {
    return value_increased * ((1 / interest) - (num_period / (pow(1 + interest, num_period) - 1)));
}

/**
 * Calculate conversion factor for geometric gradient series of present worth
 * Note: For g != i only, consider using formula P = N*(A/(1+g)) if g == i
 * @param rate_growth rate of growth per period
 * @param interest effective annual interest rate
 * @param num_period number of periods
 * @return conversion factor for geometric gradient series
 */
double EngEcoUtil::GGF(double rate_growth, double interest, int num_period) {
    double i0 = ((1 + interest) / (1 + rate_growth)) - 1;
    if (i0 == 0) {
        std::cout << "g=i>0, use P=N[A/1+g] instead" << std::endl;
        return -1;
    }
    double factor = pow(1+i0, num_period);

    return ((factor - 1) / (i0 * factor)) / (1+rate_growth);
}

/**
 * Calculate approximate IRR using linear interpolation
 * Formula is given as x* = x1 + (x2-x1)*[(y*-y1)/(y2-y1)]
 * Coefficient: result of (P/A) or other formula given result interest
 * @param target_coef y*, Coefficient given IRR
 * @param interest1 x1, the interest rate of upperbound coefficient
 * @param interest2 x2, the interest rate of lowerbound coefficient
 * @param coef1 y1, upperbound coefficient
 * @param coef2 y2, lowerbound coefficient
 * @return x*, estimated IRR
 */
double EngEcoUtil::IRR(double target_coef, double interest1, double interest2, double coef1, double coef2) {
    return interest1 + ((interest2 - interest1) * ((target_coef - coef1) / (coef2 - coef1)));
}