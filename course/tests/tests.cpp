#include "pch.h"
#include "CppUnitTest.h"
#include "../course/graph.h"
#include "../course/read.h"
#include "../course/equal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(tests)
	{
	public:
		
		TEST_METHOD(reading_empty)
		{
			graph* graph1 = new graph();
			graph* graph2 = new graph();
			read(graph1);
			Assert::IsTrue(equal_graphs(*graph1, *graph2));
		}
		TEST_METHOD(reading_2_points)
		{
			graph* graph1 = new graph();
			graph* graph2 = new graph();
			read(graph1);
			graph2->add("s", "t", 5);
			graph2->add("t", "s", 5);
			Assert::IsTrue(equal_graphs(*graph1, *graph2));
		}
		TEST_METHOD(reading_net)
		{
			graph* graph1 = new graph();
			graph* graph2 = new graph();
			read(graph1);
			graph2->add("s", "o", 3);
			graph2->add("s", "p", 3);
			graph2->add("o", "q", 3);
			graph2->add("o", "p", 2);
			graph2->add("p", "r", 2);
			graph2->add("q", "r", 4);
			graph2->add("q", "t", 2);
			graph2->add("r", "t", 3);
			Assert::IsTrue(equal_graphs(*graph1, *graph2));
		}
		TEST_METHOD(correct_sink_name)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsFalse(mygraph->transport_net_check());
		}
		TEST_METHOD(correct_source_name)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsFalse(mygraph->transport_net_check());
		}
		TEST_METHOD(correct_sink_value)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsFalse(mygraph->transport_net_check());
		}
		TEST_METHOD(correct_source_value)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsFalse(mygraph->transport_net_check());
		}
		TEST_METHOD(net)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsFalse(mygraph->transport_net_check());
		}
		TEST_METHOD(cycles)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsFalse(mygraph->transport_net_check());
		}
		TEST_METHOD(flow_5)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsTrue(equal_size_t(mygraph->find_max_flow(), 5));
		}
		TEST_METHOD(flow_8)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsTrue(equal_size_t(mygraph->find_max_flow(), 8));
		}
		TEST_METHOD(flow_3)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsTrue(equal_size_t(mygraph->find_max_flow(), 3));
		}
		TEST_METHOD(flow_1)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsTrue(equal_size_t(mygraph->find_max_flow(), 1));
		}
		TEST_METHOD(flow_0)
		{
			graph* mygraph = new graph();
			read(mygraph);
			Assert::IsTrue(equal_size_t(mygraph->find_max_flow(), 0));
		}
	};
}
