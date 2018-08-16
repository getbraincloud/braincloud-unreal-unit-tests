#include <stdlib.h>
#include "TestBCRTTComms.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"

#if __cplusplus >= 201103L
#include <chrono>
#include <thread>
#endif

TEST_F(TestBCRTTComms, RequestClientConnection)
{
	TestResult tr;

	m_bc->getRTTRegistrationService()->requestClientConnection(&tr);
	tr.run(m_bc);
}

// testEnableRTTWithWS

TEST_F(TestBCRTTComms, EnableRTTWithTCP)
{
	TestResult tr;

	m_bc->enableRTT(&tr, false);
	tr.run(m_bc);
}
