from datetime import datetime, timedelta

def is_valid_date(date_text):
    try:
        datetime.strptime(date_text, '%Y-%m-%d')
        return True
    except ValueError:
        return False

def main():
    filename = 'output_dates.txt'  
    dates_in_year = set()  
    with open(filename, 'r', encoding='utf-16') as file:
        lines = file.readlines()
        for line in lines:
            line = line.strip().strip('\ufeff')
            date_parts = line.split('-')
            if len(date_parts) == 3:
                year, month, day = map(int, date_parts)
                if 1 <= month <= 12 and 1 <= day <= 31:  
                    date = f"{year}-{month:02d}-{day:02d}"
                    if is_valid_date(date):
                        dates_in_year.add(date)
                    else:
                        print(f"{date} is not a valid date")
                else:
                    print(f"Invalid date format: {line}")
            else:
                print(f"Invalid date format: {line}")

    if len(dates_in_year) == 365:
        print("All dates in the year are present.")
    else:
        missing_dates = set()
        start_date = datetime.strptime(f"{year}-01-01", "%Y-%m-%d")
        end_date = datetime.strptime(f"{year}-12-31", "%Y-%m-%d")
        delta = timedelta(days=1)
        current_date = start_date
        while current_date <= end_date:
            date_str = current_date.strftime("%Y-%m-%d")
            if date_str not in dates_in_year:
                missing_dates.add(date_str)
            current_date += delta

        if not missing_dates:
            print("Tests Passed")
        else:
            print("Missing dates:")
            for date in sorted(missing_dates):
                print(date)

if __name__ == "__main__":
    main()
