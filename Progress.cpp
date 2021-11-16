//
// Created by user on 13.10.2020.
//

#include "Progress.h"
#include "Algorithms.h"

bool TProgress::Progress(double value)
{
    {
        TLock guard(mut);
        switch (typeProg)
        {
            case tpAbsolut:
                cur = value;
                break;

            case tpStep:
                if(value != 0.)
                    cur = cur + value;
                else
                    cur = value;
                break;
        }
        if (cur > 0. && borderProg > 0.)
        {
            if (TDoubleCheck::Less(cur, curBorder))
                return !isCancel;         //если бордюр не преодолели, то окно прогресса не вызываем
            curBorder = curBorder + borderProg; //если бордюр преодолен, то отобразим окно
        }
    }
    ViewShow();
    return !IsCancel();
}

void TProgress::Finish()
{
    Progress(maxProg + 1);
}

bool TProgress::IsFinished()
{
    TLock guard(mut);
    return cur >= maxProg;
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

void TProgress::SetResult(TResult value, bool isCall)
{
    result = value;
    if(isCall)
        CallResult();
}

void TProgress::Reset()
{
    OnResult.disconnect_all();
    result = TResult();
    cur = 0.;
    isCancel = false;
}

bool TProgress::IsCancel() const
{
    TLock guard(mut);
    return isCancel;
}

void TProgress::SetCancel()
{
    TLock guard(mut);
    isCancel = true;
}