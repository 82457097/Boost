#include<boost/asio.hpp>       
#include<iostream>
#include<boost/bind.hpp>
//#include<boost/asio/steady_timer.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<thread>

using namespace std;

/*
//同步方式
int main() {
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.wait();

	std::cout << "hello world!" << std::endl;

	system("pause");
	return 0;
}*/

//异步方式
/*
void callback(const boost::system::error_code&) {
	cout << "hello world!" << endl;
}

int main() {
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.async_wait(callback);
	io.run();

	system("pause");
	return 0;
}*/

/*
void print(const boost::system::error_code &,
	boost::asio::deadline_timer *t, int *count) {
	if (*count < 5) {
		cout << *count << endl;
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
	}
}

int main() {

	boost::asio::io_service io;

	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

	io.run();
	cout << "Final count is " << count << endl;

	system("pause");
	return 0;
}*/

/*
//Lambda函数的本质
class Lambda {
public:
	void operator()(int a) const {
		cout << a << " and " << m_b << " and " << m_c << endl;
	}
	Lambda(int b,int& c):m_b(b),m_c(c) {}
private:
	int m_b;
	int& m_c;
};

void testLambda() {
	int b = 2;
	int c = 3;
	auto lambda2 = [b, &c](int a) {cout << a << " and " << b << " and " << c << endl; };
	lambda2(1);
	cout << "sizeof lambda: " << sizeof(lambda2) << endl;

	Lambda lambda(2, c);
	lambda(1);
	cout << "sizeof lambda: " << sizeof(lambda) << endl;
}

int main() {
	testLambda();

	system("pause");
	return 0;
}*/ 

/*
class printer {
public:
	printer(boost::asio::io_service &io)
		:timer_(io, boost::posix_time::seconds(1)), count_(0) {
		timer_.async_wait(boost::bind(&printer::print, this));
	}
	~printer() { 
		cout << "Final count is " << count_ << endl; 
	}

	void print() {
		if (count_ < 5) {
			cout << count_ << endl;
			++count_;
			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&printer::print, this));
		}
	}
private:
	boost::asio::deadline_timer timer_;
	int count_;
};

int main() {
	boost::asio::io_service io;
	printer p(io);
	io.run();

	system("pause");
	return 0;
}*/

/*
class printer {
public:
	printer(boost::asio::io_service &io)
		:strand_(io), timer1_(io, boost::posix_time::seconds(1)),
		timer2_(io, boost::posix_time::seconds(1)), count_(0) {
		timer1_.async_wait(strand_.wrap([this](const auto&) {this->print1(); }));
		timer2_.async_wait(strand_.wrap([this](const auto&) {this->print2(); }));
	}
	~printer() { cout << "Final count is " << count_ << endl; }

	void print1() {
		if (count_ < 10) {
			cout << "Timer 1: " << count_ << endl;
			++count_;

			timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
			timer1_.async_wait(strand_.wrap([this](const auto&) {this->print1(); }));
		}
	}

	void print2() {
		if (count_ < 10) {
			cout << "Timer 2: " << count_ << endl;
			++count_;

			timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
			timer2_.async_wait(strand_.wrap([this](const auto&) {this->print2(); }));
		}
	}
private:
	int count_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	boost::asio::io_service::strand strand_;
};

int main() {
	boost::asio::io_service io;
	printer p(io);
	thread t([&io] {io.run(); });
	io.run();
	t.join();

	//system("pause");
	return 0;
}*/



