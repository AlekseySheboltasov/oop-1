#pragma once
#include <iostream>
#include <string>
#include "container.h"

class Object {
protected:
	static int count;
public:
	virtual std::string toString() = 0;

	void add_object() {
		count++;
	}

	void remove_object() {
		count--;
	}

	static int get_count() {
		return count;
	}
};

int Object::count = 0;

class Task : public Object {
protected:
	bool is_completed;
public:
	Task(bool completed = false) : is_completed(completed) {
		add_object();
	}

	virtual void complete() = 0;

	bool completed() {
		return is_completed;
	}

	~Task() {
		remove_object();
	}
};

class Named : public Object {
protected:
	std::string name;
public:
	Named(std::string Name = "") {
		name = Name;
	}

	~Named() {
	}
};

class Binary : public Task, public Named {
protected:
	double arg1;
	double arg2;
	double result = NULL;
public:
	Binary(std::string n, double a1, double a2, bool completed = false, double res = 0) :
		Named(n), arg1(a1), arg2(a2), Task(completed), result(res) {}

	virtual void complete() {
		if (name == "+") {
			result = arg1 + arg2;
		}
		else if (name == "-") {
			result = arg1 - arg2;
		}
		else if (name == "*") {
			result = arg1 * arg2;
		}
		else if (name == "/") {
			result = arg1 / arg2;
		}
		else {
			throw std::invalid_argument("Invalid operand");
		}
		is_completed = true;
	}

	double get_result() {
		if (!is_completed) {
			complete();
		}
		return result;
	}

	virtual std::string toString() {
		std::string info = "Binary operation " + name;
		if (result) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};

class Add_Task : public Task {
protected:
	Container<Task*>* container;
	Task* task;
public:
	Add_Task(Container<Task*>* cont, Task* t, bool completed = false) :
		container(cont), task(t), Task(completed) {}

	virtual void complete() {
		if (container && task) {
			container->push(task);
			is_completed = true;
		}
		else {
			throw std::logic_error("Container or task is not defined");
		}
	}

	virtual std::string toString() {
		std::string info = "Task of pushing to container is ";
		if (!is_completed) {
			info += "not ";
		}
		info += "completed\n";
		return info;
	}
};

class Count_Objects : public Task {
protected:
	Container<Task*>* container;
	int result = NULL;
public:
	Count_Objects(Container<Task*>* cont, bool completed = false) : container(cont), Task(completed) {}

	virtual void complete() {
		if (container) {
			result = container->size();
			is_completed = true;
		}
		else {
			throw std::logic_error("Container is not defined");
		}
	}

	virtual std::string toString() {
		std::string info = "Task of counting Objects in container ";
		if (result) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};

class Count_Results : public Task {
protected:
	Container<Task*>* container;
	int result = NULL;
public:
	Count_Results(Container<Task*>* cont, bool completed = false) : container(cont), Task(completed) {}

	virtual void complete() {
		if (container) {
			result = 0;
			for (auto i = container->begin(); i != container->end(); ++i) {
				if ((i.value())->completed()) {
					result++;
				}
			}
			is_completed = true;
		}
		else {
			throw std::logic_error("Container is not defined");
		}
	}

	virtual std::string toString() {
		std::string info = "Task of counting resulted tasks in container ";
		if (result) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};

class Clear_Task : public Task {
protected:
	Container<Task*>* container;
public:
	Clear_Task(Container<Task*>* cont, bool completed = false) : container(cont), Task(completed) {}

	virtual void complete() {
		if (container) {
			container->clear();
			is_completed = true;
		}
		else {
			throw std::logic_error("Container is not defined");
		}
	}

	virtual std::string toString() {
		std::string info = "Task of clearing container is ";
		if (!is_completed) {
			info += "not ";
		}
		info += "completed\n";
		return info;
	}
};

class All_Objects : public Task {
protected:
	int result = NULL;
public:
	All_Objects(bool completed = false) : Task(completed) {}

	virtual void complete() {
		result = count;
		is_completed = true;
	}

	virtual std::string toString() {
		std::string info = "Task of counting all objects in program ";
		if (result) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};