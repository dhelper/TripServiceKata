#include "gmock_catch_interceptor.h"

#include "catch.hpp"

using namespace ::testing;

void gmock_catch_interceptor::OnTestPartResult(const testing::TestPartResult& result)
{
	std::string filename = "unknown";
	size_t lineNumber = 0;
	std::string message = "unknown";
	if (result.file_name() != nullptr)
		filename = result.file_name();

	if (result.line_number() != -1)
		lineNumber = static_cast<std::size_t>(result.line_number());

	if (result.message() != nullptr)
		message = result.message();

	::Catch::SourceLineInfo sourceLineInfo(filename.c_str(), lineNumber);

	if (result.fatally_failed()) {
		::Catch::AssertionHandler assertion("GTEST", sourceLineInfo, "", ::Catch::ResultDisposition::Normal);

		assertion.handleMessage(::Catch::ResultWas::ExplicitFailure, message);
		assertion.setCompleted();

	}
	else if (result.nonfatally_failed()) {
		::Catch::AssertionHandler assertion("GTEST", sourceLineInfo, "", ::Catch::ResultDisposition::ContinueOnFailure);

		assertion.handleMessage(::Catch::ResultWas::ExplicitFailure, message);
		assertion.setCompleted();
	}
}

void gmock_catch_interceptor::OnTestProgramStart(const UnitTest& unit_test) {}
void gmock_catch_interceptor::OnTestIterationStart(const UnitTest& unit_test, int iteration) {}
void gmock_catch_interceptor::OnEnvironmentsSetUpStart(const UnitTest& unit_test) {}
void gmock_catch_interceptor::OnEnvironmentsSetUpEnd(const UnitTest& unit_test) {}
void gmock_catch_interceptor::OnTestCaseStart(const TestCase& test_case) {}
void gmock_catch_interceptor::OnTestStart(const TestInfo& test_info) {}
void gmock_catch_interceptor::OnTestEnd(const TestInfo& test_info) {}
void gmock_catch_interceptor::OnTestCaseEnd(const TestCase& test_case) {}
void gmock_catch_interceptor::OnEnvironmentsTearDownStart(const UnitTest& unit_test) {}
void gmock_catch_interceptor::OnEnvironmentsTearDownEnd(const UnitTest& unit_test) {}
void gmock_catch_interceptor::OnTestIterationEnd(const UnitTest& unit_test, int iteration) {}
void gmock_catch_interceptor::OnTestProgramEnd(const UnitTest& unit_test) {}
