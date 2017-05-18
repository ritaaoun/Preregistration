#include "parser.h"
#include <QDebug>

Parser::Parser()
{

}


std::vector<std::string> Parser::getStdVector(std::vector<QString> qStringVector)
{
    std::vector<std::string> stringVector;

    for(int i = 0; i < qStringVector.size(); i++)
    {
        stringVector.push_back(qStringVector[i].toStdString());
    }

    return stringVector;
}

std::string Parser::sendActiveUser()
{
    return User::getUser()->getUsername().toStdString();
}

std::string Parser::sendCredentials(std::string username, std::string password)
{
    std::string result;

    result = username + ClientServerInterface::DELIMITER + password;

    return result;
}

void Parser::getCreateUser(std::string message)
{
    //split
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::DELIMITER);

    User::getUser()->setUsername(messageVector[0]);
    User::getUser()->setId(std::stoi(messageVector[1]));
    User::getUser()->setName(messageVector[2] + " " + messageVector[3] + " " + messageVector[4]);
    User::getUser()->setDepartmentId(std::stoi(messageVector[5]));
    User::getUser()->setBirthday(messageVector[6]);
    User::getUser()->setStartYear(messageVector[7]);
    User::getUser()->setStartTerm(messageVector[8]);
    std::string type = messageVector[9];

    if(type == "2")
    {
        User::getUser()->setType(User::Type::ADMINISTRATOR);
    }
    else if (type == "1")
    {
        User::getUser()->setType(User::Type::PROFESSOR);
    }
    else if (type == "0")
    {
        User::getUser()->setType(User::Type::STUDENT);
    }
}

bool Parser::getBoolean(std::string message)
{
    if(message == "true")
    {
        return true;
    }

    return false;
}

std::string Parser::sendCreateUserInfo(std::string admin, std::vector<std::string> userInfo)
{
    std::string result = admin;

    for(int i = 0; i < userInfo.size(); i++)
    {
        result += ClientServerInterface::DELIMITER + userInfo[i];
    }

    return result;
}

std::unordered_map<int, QString> Parser::getDepartments(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::unordered_map<int, QString> map;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        map[std::stoi(object[0])] = QString::fromStdString(object[1]);
    }

    return map;
}

std::vector<UserInfo> Parser::getAdminUserInfo(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<UserInfo> userInfo;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        UserInfo user;
        user.setUsername(QString::fromStdString(object[0]));
        user.setId(std::stoi(object[1]));
        user.setFirstName(QString::fromStdString(object[2]));
        user.setMiddleName(QString::fromStdString(object[3]));
        user.setLastName(QString::fromStdString(object[4]));
        user.setDedepartment(std::stoi(object[5]));
        user.setDateOfBirth(QDate::fromString(QString::fromStdString(object[6])));
        user.setStartYear(std::stoi(object[7]));
        user.setStartTerm(std::stoi(object[8]));
        user.setUserType(std::stoi(object[9]));

        userInfo.push_back(user);
    }

    return userInfo;
}

std::vector<Message> Parser::getUserMessages(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<Message> userMessages;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        Message message;

        message.setFrom(object[0]);
        message.setTo(object[1]);
        message.setSubject(object[2]);
        message.setMessage(object[3]);

        userMessages.push_back(message);
    }

    return userMessages;
}

std::string Parser::sendMessage(Message message)
{
    std::string result;

    result = message.getFromStdString()
            + ClientInterface::DELIMITER + message.getToStdString()
            + ClientInterface::DELIMITER + message.getSubjectStdString()
            + ClientInterface::DELIMITER + message.getMessageStdString();

    return result;
}

std::string Parser::sendPrivilges(std::string username, std::string adminUsername, std::string department)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + adminUsername
            + ClientInterface::DELIMITER + department;

    return result;
}

std::vector<Course> Parser::getCourseRequests(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<Course> courses;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        Course course;
        course.setId(stoi(object[0]));
        course.setCode(object[1]);
        course.setName(object[2]);
        course.setDescription(object[3]);
        course.setCredits(std::stoi(object[4]));

        courses.push_back(course);
    }

    return courses;
}

std::string Parser::sendDecideOnCourse(std::string username, int id, bool accepted)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + std::to_string(id)
            + ClientInterface::DELIMITER + std::to_string(accepted);

    return result;
}

std::string Parser::sendChangePassword(std::string username, std::string oldPassowrd, std::string newPassword)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + oldPassowrd
            + ClientInterface::DELIMITER + newPassword;

    return result;
}

std::string Parser::sendResetPassword(std::string username, std::string userUsername)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + userUsername;

    return result;
}

std::string Parser::sendPusblishSection(std::string username, int courseId, int capacity, std::vector<TimeSlot> timeSlots)
{
    std::string result = username
            + ClientInterface::DELIMITER + std::to_string(courseId)
            + ClientInterface::DELIMITER + std::to_string(capacity);

    if (timeSlots.size() > 0)
    {
        result += ClientServerInterface::DELIMITER;
        for (std::vector<TimeSlot>::iterator it = timeSlots.begin(); it != timeSlots.end(); ++it)
        {
            result += (*it).getDayStdString()
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getStartHour())
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getStartMinutes())
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getEndHour())
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getEndMinutes());

            if (timeSlots.end() != it + 1)
            {
                result += ClientServerInterface::LIST_TIMESLOT_DELIMITER;
            }
        }
    }
    return result;
}

std::string Parser::sendEditSection(std::string username, int crn, int capacity, std::vector<TimeSlot> timeSlots)
{
    std::string result = username
            + ClientInterface::DELIMITER + std::to_string(crn)
            + ClientInterface::DELIMITER + std::to_string(capacity);

    if (timeSlots.size() > 0)
    {
        result += ClientServerInterface::DELIMITER;
        for (std::vector<TimeSlot>::iterator it = timeSlots.begin();it != timeSlots.end();++it)
        {
            result += (*it).getDayStdString()
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getStartHour())
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getStartMinutes())
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getEndHour())
                    + ClientServerInterface::TIMESLOT_DELIMITER + std::to_string((*it).getEndMinutes());

            if (timeSlots.end() != it + 1)
            {
                result += ClientServerInterface::LIST_TIMESLOT_DELIMITER;
            }
        }
    }
    return result;
}

std::vector<Course> Parser::getSections(std::string message)
{
    // seperate the sections
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);
    QMap<std::string, Course> idCourseMap;

    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        Section section;
        Course course;
        if(!idCourseMap.contains(object[1]))
        {
            course.setId(stoi(object[1]));
            course.setCode(object[2]);
            course.setName(object[3]);
            course.setDescription(object[4]);
            course.setCredits(std::stoi(object[5]));
            idCourseMap.insert(object[1], course);
        }
        else
        {
            course = idCourseMap[object[1]];
        }

        section.setCrn(stoi(object[0]));
        section.setNumber(stoi(object[6]));
        section.setCapacity(stoi(object[7]));
        section.setStudentCount(stoi(object[8]));
        section.setProfessorName(object[9]);
        std::string timeslots = object[10];

        std::vector<std::string> timeslotsStrings = ClientInterface::split(timeslots, ClientInterface::LIST_TIMESLOT_DELIMITER);

        for(int j = 0; j < timeslotsStrings.size(); j++)
        {
            std::vector<std::string> timeSlotElements = ClientInterface::split(timeslotsStrings[j], ClientInterface::TIMESLOT_DELIMITER);

            TimeSlot timeSlot;
            timeSlot.setDayString(timeSlotElements[0]);
            timeSlot.setStartHour(stoi(timeSlotElements[1]));
            timeSlot.setStartMinutes(stoi(timeSlotElements[2]));
            timeSlot.setEndHour(stoi(timeSlotElements[3]));
            timeSlot.setEndtMinutes(stoi(timeSlotElements[4]));

            section.addTimeSlot(timeSlot);
        }

        section.setStatus(std::stoi(object[11]));
        section.setRoom(object[12]);

        course.addSection(section);
        idCourseMap.insert(object[1], course);
    }

    std::vector<Course> courses;
    for (QMap<std::string, Course>::iterator it = idCourseMap.begin(); it != idCourseMap.end(); ++it)
        courses.push_back(*it);

    return courses;
}

std::string Parser::sendRequestCourse(std::string username, std::string courseName, std::string courseNumber, std::string courseDescription,
                                     int numberOfCreadits, bool needsComputers, bool needsSpeakers, bool needsHighEnergyParticleAccelerator)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + courseNumber
            + ClientInterface::DELIMITER + courseName
            + ClientInterface::DELIMITER + courseDescription
            + ClientInterface::DELIMITER + std::to_string(numberOfCreadits)
            + ClientInterface::DELIMITER + std::to_string(needsComputers)
            + ClientInterface::DELIMITER + std::to_string(needsSpeakers)
            + ClientInterface::DELIMITER + std::to_string(needsHighEnergyParticleAccelerator);

    return result;
}

std::string Parser::sendRemoveSection(std::string username, int crn)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + std::to_string(crn);

    return result;
}

std::string Parser::sendAddSection(std::string username, int crn)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + std::to_string(crn);

    return result;
}

std::string Parser::sendConfirmSection(std::string username, int crn)
{
    std::string result;

    result = username
            + ClientInterface::DELIMITER + std::to_string(crn);

    return result;
}

std::vector<Course> Parser::getDepartmentCourses(std::string message)
{
    std::vector<std::string> messageVector = ClientInterface::split(message, ClientInterface::LIST_DELIMITER);

    std::vector<Course> courses;
    for(int i = 0; i < messageVector.size(); i++)
    {
        std::vector<std::string> object = ClientInterface::split(messageVector[i], ClientInterface::DELIMITER);

        Course course;
        course.setId(std::stoi(object[0]));
        course.setCode(object[1]);
        course.setName(object[2]);
        course.setDescription(object[3]);
        course.setCredits(std::stoi(object[4]));

        courses.push_back(course);
    }

    return courses;
}
