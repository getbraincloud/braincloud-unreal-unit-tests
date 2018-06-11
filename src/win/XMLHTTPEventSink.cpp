#include "braincloud/internal/win/XMLHTTPEventSink.h"

#include <iostream>
#include <string>

STDMETHODIMP XMLHTTPEventSink::QueryInterface(const IID &riid, void **ppvObject)
{
    if (ppvObject == NULL)
        return E_INVALIDARG;

    *ppvObject = NULL;

    if (riid == IID_IUnknown)
        *ppvObject = static_cast<IUnknown*>(this);
    else if (riid == IID_IDispatch)
        *ppvObject = static_cast<IDispatch*>(this);

    if (*ppvObject == NULL)
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}

STDMETHODIMP_(ULONG) XMLHTTPEventSink::AddRef()
{
    return InterlockedIncrement(&m_refCount);
}


STDMETHODIMP_(ULONG) XMLHTTPEventSink::Release()
{
    LONG refCount = InterlockedDecrement(&m_refCount);
    if (refCount == 0)
    {
        delete this;
        return 0;
    }
    else
        return refCount;
}

STDMETHODIMP XMLHTTPEventSink::GetTypeInfoCount(UINT *pctinfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP XMLHTTPEventSink::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP XMLHTTPEventSink::GetIDsOfNames(const IID &riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    return E_NOTIMPL;
}

STDMETHODIMP XMLHTTPEventSink::Invoke(DISPID dispIdMember, const IID &riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    // Retrieve the state
    long state;
    m_request->get_readyState(&state);

    if (state == 4)
    {
        // Signal the main thread we're done.
        m_onCompleted();
    }

    return S_OK;
}

