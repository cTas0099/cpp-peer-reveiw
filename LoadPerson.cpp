struct LoadPersonStruct {
    int db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel& db_log_level;
    int min_age;
    int max_age;

    LoadPersonStruct& SetDbConnectionTimeout(int db_connection_timeout) {
        this->db_connection_timeout = db_connection_timeout;
        return *this;
    }

    LoadPersonStruct& SetDbAllowExceptions(bool db_allow_exceptions) {
        this->db_allow_exceptions = db_allow_exceptions;
        return *this;
    }

    LoadPersonStruct& SetDbLogLevel(DBLogLevel& db_log_level) {
        this->db_log_level = db_log_level;
        return *this;
    }

    LoadPersonStruct& SetMinAge(int min_age) {
        this->min_age = min_age;
        return *this;
    }

    LoadPersonStruct& SetMaxAge(int max_age) {
        this->max_age = max_age;
        return *this;
    }
};

vector<Person> LoadPersons(string_view db_name, LoadPersonStruct& person_struct,
                           string_view name_filter) {
    DBConnector connector(person_struct.db_allow_exceptions, person_struct.db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_name, person_struct.db_connection_timeout);
    } else {
        db = connector.Connect(db_name, person_struct.db_connection_timeout);
    }
    if (!person_struct.db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << person_struct.min_age << " and "s << person_struct.max_age << " "s
              << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}
