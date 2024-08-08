#pragma once
namespace car {
    class CCar;  //提前声明CCar类，以便后面的CDriver类使用
    class CDriver
    {
    public:
        void ModifyCar(CCar* pCar);  //改装汽车
    };
    class CCar
    {
    private:
        int price;
        friend int MostExpensiveCar(CCar cars[], int total);  //声明友元
        friend void CDriver::ModifyCar(CCar* pCar);  //声明友元
    };
    void CDriver::ModifyCar(CCar* pCar)
    {
        pCar->price += 1000;  //汽车改装后价值增加
    }
}