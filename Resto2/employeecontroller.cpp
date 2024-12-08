#include "employeecontroller.h"

EmployeeController::EmployeeController(QObject *parent) : QObject(parent) {}

void EmployeeController::addEmployee(Employee *employee) {
    employees.append(employee);
}

Employee *EmployeeController::findEmployeeById(int employeeId) {
    for (Employee *employee : employees) {
        if (employee->getId() == employeeId) {
            return employee;
        }
    }
    return nullptr;
}

QVector<Employee*> EmployeeController::getEmployees() const {
    return employees;
}
