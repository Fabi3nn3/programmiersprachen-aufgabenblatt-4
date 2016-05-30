#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include "List.hpp"

TEST_CASE("EmptyTest","[Test ob Liste geht]"){

	List<int> list1;
	REQUIRE(list1.empty()==true);

}

TEST_CASE("SizeTest","[TesteSize]"){

	List<int> list2;
	REQUIRE(list2.size()==0);

}

TEST_CASE("add an element with push_front", "[modifiers]"){

	List<int> list;
	list.push_front(42);
	REQUIRE(42 == list.front());

	list.push_front(69);
	list.push_front(33);
	REQUIRE(33 == list.front());
	
}


TEST_CASE("add an element with push_back", "[modifiers]"){

	List<int> list;
	list.push_back(42);
	REQUIRE(42 == list.back());

	list.push_back(69);
	list.push_back(33);
	REQUIRE(33 == list.back());

	
}


TEST_CASE("remove an element with pop_front", "[modifiers]"){

	List<int> list{};
	list.push_back(42);
	list.pop_front();
	REQUIRE(true == list.empty());

	list.push_back(69);
	list.push_back(96);
	list.pop_front();
	REQUIRE(list.front() == 96);
	
}

TEST_CASE("remove an element with pop_back", "[modifiers]"){

	List<int> list{};
	list.push_back(42);
	list.pop_back();
	REQUIRE(true == list.empty());

	list.push_back(69);
	list.push_back(96);
	list.pop_back();
	REQUIRE(list.front() == 69);

}

TEST_CASE("should be empty after clearing","[modifiers]"){

	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.clear();
	REQUIRE(list.empty() == true);
}

int main(int argc, char *argv[]){

	return Catch::Session().run(argc,argv);
}