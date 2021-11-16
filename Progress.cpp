//
// Created by user on 13.10.2020.
//

#include "Progress.h"
#include "Base/Algorithms.h"

void TProgress::Progress(double value)
{
    {
        TLock guard(mut);
        switch (typeProg)
        {
            case tpAbsolut:
                cur = value;
                break;

            case tpStep:
                cur = cur + value;
                break;
        }
        if (value != 0. && borderProg != 0.)
        {
            if (TDoubleCheck::Less(cur, curBorder))
                return;         //если бордюр не преодолели то окно прогресса не вызываем
            curBorder = curBorder + borderProg; //если бордюр преодолен, то отобразим окно
        }
    }
    ViewShow();
}

void TProgress::Finish()
{
    Progress(maxProg + 1);
}

bool TProgress::IsSend() const
{
    return isSend;
}

TProgress &TProgress::SetIsSend(bool value)
{
    isChanged = isSend != value;
    isSend = value;
    return *this;
}

double TProgress::Border() const
{
    return borderProg;
}

TProgress &TProgress::SetBorder(double value)
{
    isChanged = borderProg != value;
    borderProg = value;
    curBorder = borderProg;
    return *this;
}

TProgress::TTypeProgress TProgress::TypeProgress() const
{
    return typeProg;
}

TProgress &TProgress::SetTypeProgress(TProgress::TTypeProgress value)
{
    isChanged = typeProg != value;
    typeProg = value;
    return *this;
}

const TString &TProgress::Text() const
{
    return text;
}

TProgress &TProgress::SetText(const TString &value)
{
    isChanged = text != value;
    text = value;
    return *this;
}

double TProgress::Max() const
{
    return maxProg;
}

TProgress &TProgress::SetMax(double value)
{
    isChanged = maxProg != value;
    maxProg = value;
    return *this;
}

void TProgress::SetBorderOfMax(double coef)
{
    SetBorder(maxProg * coef);
}

TProgress &TProgress::SetMaxAndBorderCoef(double value, double coef)
{
    SetMax(value);
    SetBorderOfMax(coef);
    return *this;
}

void TProgress::SetError(TResult value)
{
    TLock lock(mut);
    error = value;
}

//-----------------------------------------------------------------------------------------------------------
TPoolFunction* TPoolFunction::Create(TPtrProgress progress)
{
    TPoolFunction* res = new TPoolFunction();//создаем пулл функций
    res->ptr.reset(res);//отдаем ему на хранение
    res->progress = progress;
    return res;
}

void TPoolFunction::Start()
{
    results = 0;

    if(functions.empty())
    {
        ptr.reset();//освобождаем
        return;
    }

    if(progress)
    {
        progress->SetIsSend(true);
        progress->SetTypeProgress(TProgress::tpStep);
        progress->SetMax(functions.size());
    }
    for(const auto& fun : functions)
    {
        std::thread t(
                [this, fun]() {

                    TResult res = fun();
                    if(res.IsError())//если была ошибка выполнения
                    {
                        TLock lock(mut);
                        if(error.IsNoError())//сохраняем только первую ошибку из списка
                        {
                            error = res;
                            if (progress) progress->SetError(error);
                        }
                    }
                    results++;
                    if (progress) progress->Progress(1.);
                    if (results == functions.size())
                    {
                        OnFinish(error);
                        ptr.reset();
                    }
                });
        t.detach();
    }
}

void TPoolFunction::Add(TPoolFunction::TCallFunction value)
{
    functions.push_back(value);
}

void TPoolFunction::Reset()
{
    ptr.reset();//освобождаем
}

