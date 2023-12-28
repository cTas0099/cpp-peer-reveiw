class ParserJson {
public:

    // ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
    void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
        for (const auto& country_json : json.AsList()) {
            const auto& country_obj = country_json.AsObject();
            countries.push_back({
                country_obj["name"s].AsString(),
                country_obj["iso_code"s].AsString(),
                country_obj["phone_code"s].AsString(),
                country_obj["time_zone"s].AsString(),
            });
            Country& country = countries.back();
            for (const auto& lang_obj : country_obj["languages"s].AsList()) {
                country.languages.push_back(FromString<Language>(lang_obj.AsString()));
            }
            ParseCitySubjson(ParseCitySubjsonStruct().SetCities(cities).SetJson(country_obj["cities"s]).
                SetCountryName(country.name).SetCountryIsoCode(country.iso_code).
                SetCountryPhoneCode(country.phone_code).SetCountryTimeZone(country.time_zone).
                SetLanguages(country.languages));
        }
    }
private:

    struct ParseCitySubjsonStruct {
        vector<City>* cities;
        const Json* json;
        const string* country_name;
        const string* country_iso_code;
        const string* country_phone_code;
        const string* country_time_zone;
        const vector<Language>* languages;

        ParseCitySubjsonStruct& SetCities(vector<City>& cities) {
            this->cities = &cities;
            return *this;
        }
        ParseCitySubjsonStruct& SetJson(const Json& json) {
            this->json = &json;
            return *this;
        }
        ParseCitySubjsonStruct& SetCountryName(const string& country_name) {
            this->country_name = &country_name;
            return *this;
        }
        ParseCitySubjsonStruct& SetCountryIsoCode(const string& country_iso_code) {
            this->country_iso_code = &country_iso_code;
            return *this;
        }
        ParseCitySubjsonStruct& SetCountryPhoneCode(const string& country_phone_code) {
            this->country_phone_code = &country_phone_code;
            return *this;
        }
        ParseCitySubjsonStruct& SetCountryTimeZone(const string& country_time_zone) {
            this->country_time_zone = &country_time_zone;
            return *this;
        }
        ParseCitySubjsonStruct& SetLanguages(const vector<Language>& languages) {
            this->languages = &languages;
            return *this;
        }
    };
    // Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
    void ParseCitySubjson(ParseCitySubjsonStruct) {
        for (const auto& city_json : json.AsList()) {
            const auto& city_obj = city_json.AsObject();
            cities.push_back({city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                              country_phone_code + city_obj["phone_code"s].AsString(), country_name, country_iso_code,
                              country_time_zone, languages});
        }
    }

};
