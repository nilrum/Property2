//
// Created by user on 13.10.2020.
//

#ifndef NEO_PROGRESS_H
#define NEO_PROGRESS_H

#include "Result.h"
#include <mutex>
#include "sigslot/signal.hpp"

using TLock = std::lock_guard<std::mutex>;
using TUniqueLock = std::unique_lock<std::mutex>;

class TProgress{
public:
    virtual ~TProgress(){};
    enum TTypeProgress{tpAbsolut = 0, tpStep};

    double Border() const;
    TProgress& SetBorder(double value);
    void SetBorderOfMax(double coef);

    TTypeProgress TypeProgress() const;
    TProgress& SetTypeProgress(TTypeProgress value);

    const TString& Text() const;
    TProgress& SetText(const TString& value);

    double Max() const;
    TProgress& SetMax(double value);

    TProgress& SetMaxAndBorderCoef(double value, double coef);

    bool Progress(double value);//отправить значение прогресса и возвращает можно ли продолжить
    void Finish();              //отправить максимум и закрыть диалог
    bool IsFinished();          //возвращает активность прогресса

    void Reset();

    bool IsCancel() const;
    void SetCancel();

    void SetResult(TResult value, bool isCall = true);
    sigslot::signal<TResult> OnResult;

protected:
    TTypeProgress typeProg = tpAbsolut;
    mutable std::mutex mut;

    double cur = 0.;        //текущее положение прогресса
    double maxProg = 10.;   //максимальное значение прогресса
    double borderProg = 0.; //пороговое значение для обновления отображения прогресса
    double curBorder = 0.;  //текуший порог обновления
    TString text;
    bool isChanged = true;  //изменились ли параметры прогресса
    bool isCancel = false;  //отменили прогресс
    TResult result;

    //функции вызываемые из главного потока
    virtual void ViewShow(){};
    virtual void CallResult(){ OnResult(result); };
};

CLASS_PTRS(Progress)
#endif