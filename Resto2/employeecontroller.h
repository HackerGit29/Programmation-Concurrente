#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include <QVector>
#include "employee.h"

class EmployeeController : public QObject {
    Q_OBJECT

public:
    EmployeeController(QObject *parent = nullptr);
    void addEmployee(Employee *employee);
    Employee *findEmployeeById(int employeeId);
    QVector<Employee*> getEmployees() const;

private:
    QVector<Employee*> employees; // Liste des employés dans le restaurant
};

#endif // EMPLOYEECONTROLLER_H
