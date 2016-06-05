#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include "List.hpp"

template <typename T>
List<T> reverse(List<T> const& l){

	List<T> n{l}; //kopie von l
	n.reverse();
	return n;
}

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

	List<int> list2;
	list2.push_front(69);
	list2.push_front(33);
	REQUIRE(33 == list2.front());

	List<int> list3;
	list3.push_front(56);
	list3.push_front(44);
	list3.push_front(23);
	list3.push_front(96);
	REQUIRE(96 == list3.front());
	
}


TEST_CASE("add an element with push_back", "[modifiers]"){

	List<int> list;
	list.push_back(42);
	REQUIRE(42 == list.back());

	List<int> list2;
	list2.push_back(69);
	list2.push_back(33);
	REQUIRE(33 == list2.back());



	
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

TEST_CASE("should be an empty range after default construction","[iterators]"){

	List<int> list;
	auto b = list.begin();
	auto e = list.end();
	REQUIRE( b == e);
}

TEST_CASE("provide acces to the first element with begin","[iterators]"){

	List<int> list;
	list.push_front(42);
	REQUIRE( 42 == *list.begin());
}

TEST_CASE("equal or not","[equal]"){

	
	List<int> list3;
	list3.push_front(42);
	list3.push_front(69);
	list3.push_front(404);

	List <int> list4;
	list4.push_front(42);
	list4.push_front(69);
	list4.push_front(404);
	REQUIRE(list3 == list4);

}

TEST_CASE("different or not","[different or not]"){

	List<int> list;
	list.push_front(42);
	list.push_front(69);
	list.push_front(404);

	List <int> list2;
	list2.push_front(42);
	list2.push_front(6);
	list2.push_front(404);
	REQUIRE(list3 != list4);

}

TEST_CASE("copy constructor","[constructor]"){

	List<int> list;
	list.push_front (1);
	list.push_front (2);
	list.push_front (3);
	list.push_front (4);
	List<int> list2{list};
	REQUIRE(list == list2);


}


TEST_CASE("insert","[insert]"){

	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.push_front(5);
	list.push_front(6);

	ListIterator<int> i = list.begin();
	i++;
	i++;

	list.insert(100,i);

	REQUIRE(list.size() == 7);
	REQUIRE(*list.begin() == 6);
}

TEST_CASE("reverses the sequence of the list", "[reverse]") {
   
  List<int> list; 
  list.push_back(1); 
  list.push_back(2); 
  list.push_back(3); 
  list.push_back(4); 
  list.push_back(5);
  list.push_back(6);

  list.reverse();
  ListIterator<int> i = list.begin();
  REQUIRE(6 == *i);
  ++i;
  REQUIRE(5 == *i);
  ++i;
  REQUIRE(4 == *i);
  ++i; 
  REQUIRE(3 == *i);
  ++i;
  REQUIRE(2 == *i);
  ++i; 
  REQUIRE(1 == *i);

  reverse(list);
  ListIterator<int> it = list.begin();
  REQUIRE(6 == *it);
  ++it;
  REQUIRE(5 == *it);
  ++it;
  REQUIRE(4 == *it);
  ++it; 
  REQUIRE(3 == *it);
  ++it;
  REQUIRE(2 == *it);
  ++it; 
  REQUIRE(1 == *it);


}


TEST_CASE("move constructor","[constructor]"){

	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	List<int> list2(std::move(list));
	REQUIRE( 0 == list.size());
	REQUIRE(list.empty());
	REQUIRE(4 == list2.size());
}

int main(int argc, char *argv[]){

	return Catch::Session().run(argc,argv);
}