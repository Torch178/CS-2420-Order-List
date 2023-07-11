#ifndef MEMBERDO
#define MEMBERDO

#include "LinkedList.h"
#include <string>

class MemberDO
{
	private:
		int key;
		std::string lastName;
		char firstInit;
		double dues;
	public:
		MemberDO();
		MemberDO(int, std::string, char, double);

		int getKey() const;
		void setKey(int);
		std::string getLastName() const;
		void setLastName(std::string);
		char getFirstInitial() const;
		void setFirstInitial(char);
		double getDues() const;
		void setDues(double);

		friend bool operator==(const MemberDO& lhs, const MemberDO& rhs) { return lhs.getKey() == rhs.getKey(); }
		friend bool operator!=(const MemberDO& lhs, const MemberDO& rhs) { return !(lhs == rhs); }
		friend bool operator<(const MemberDO& lhs, const MemberDO& rhs) { return lhs.getKey() < rhs.getKey(); }
		friend bool operator>(const MemberDO& lhs, const MemberDO& rhs) { return rhs < lhs; }
		friend bool operator<=(const MemberDO& lhs, const MemberDO& rhs) { return !(lhs > rhs); }
		friend bool operator>=(const MemberDO& lhs, const MemberDO& rhs) { return !( lhs < rhs); }

		friend std::ostream& operator<< (std::ostream& out, const MemberDO& obj);
};

#endif
