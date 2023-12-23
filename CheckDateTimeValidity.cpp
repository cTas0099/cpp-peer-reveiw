class DateTimeError : public exception{
public:
    explicit DateTimeError(int num) : num_(num) {}
    int operator()(int num) {
        return num_ = num;
    }
    const char* what() const noexcept  override{
        return error_messages[num_].c_str();
    }

private:
    int num_;
    vector<string> error_messages = {
        "year is too small",
        "year is too big",
        "month is too small",
        "month is too big",
        "day is too small",
        "day is too big",
        "hour is too small",
        "hour is too big",
        "minute is too small",
        "minute is too big",
        "second is too small",
        "second is too big"
        };
};

class CheckDateTimeValid {
public:
	void CheckDateTimeValidity(const DateTime& dt) {
		if (dt.year < 1) {
            throw DateTimeError((int)DateTimeErrors::YEAR_IS_TOO_SMALL);
		}
		if (dt.year > 9999) {
			throw DateTimeError((int)DateTimeErrors::YEAR_IS_TOO_BIG);
		}

        if (dt.month < 1) {
			throw DateTimeError((int)DateTimeErrors::MONTH_IS_TOO_SMALL);
		}
		if (dt.month > 12) {
			throw DateTimeError((int)DateTimeErrors::MONTH_IS_TOO_BIG);
		}

		const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
		const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		if (dt.day < 1) {
			throw DateTimeError((int)DateTimeErrors::DAY_IS_TOO_SMALL);
		}
		if (dt.day > month_lengths[dt.month - 1]) {
			throw DateTimeError((int)DateTimeErrors::DAY_IS_TOO_BIG);
		}

		if (dt.hour < 0) {
			throw DateTimeError((int)DateTimeErrors::HOUR_IS_TOO_SMALL);
		}
		if (dt.hour > 23) {
			throw DateTimeError((int)DateTimeErrors::HOUR_IS_TOO_BIG);
		}

		if (dt.minute < 0) {
			throw DateTimeError((int)DateTimeErrors::MINUTE_IS_TOO_SMALL);
		}
		if (dt.minute > 59) {
			throw DateTimeError((int)DateTimeErrors::MINUTE_IS_TOO_BIG);
		}

		if (dt.second < 0) {
			throw DateTimeError((int)DateTimeErrors::SECOND_IS_TOO_SMALL);
		}
		if (dt.second > 59) {
			throw DateTimeError((int)DateTimeErrors::SECOND_IS_TOO_BIG);
		}
	}

private:
	enum class DateTimeErrors {
		YEAR_IS_TOO_SMALL,
		YEAR_IS_TOO_BIG,
		MONTH_IS_TOO_SMALL,
		MONTH_IS_TOO_BIG,
		DAY_IS_TOO_SMALL,
		DAY_IS_TOO_BIG,
		HOUR_IS_TOO_SMALL,
		HOUR_IS_TOO_BIG,
		MINUTE_IS_TOO_SMALL,
		MINUTE_IS_TOO_BIG,
		SECOND_IS_TOO_SMALL,
		SECOND_IS_TOO_BIG,

	};
};
