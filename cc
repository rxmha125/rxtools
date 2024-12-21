<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Weather App</title>
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.6.0/css/all.min.css" integrity="sha512-Kc323vGBEqzTmouAECnVceyQqyqdsSiqLQISBL29aUW4U/M7pSPA/gEUZQqv1cwx4OnYxTxve5UMg5GT6L4JJg==" crossorigin="anonymous" referrerpolicy="no-referrer" />
    <style>
        /* Universal Styling */
        body {
            font-family: 'Poppins', sans-serif;
            background: linear-gradient(
                135deg,
                rgba(255, 94, 87, 0.8),
                rgba(252, 175, 69, 0.8),
                rgba(84, 220, 168, 0.8),
                rgba(64, 193, 255, 0.8),
                rgba(199, 88, 233, 0.8)
            );
            background-size: 400% 400%;
            animation: gradientAnimation 10s ease infinite;
            color: #fff;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }

        @keyframes gradientAnimation {
            0% { background-position: 0% 50%; }
            50% { background-position: 100% 50%; }
            100% { background-position: 0% 50%; }
        }

        .weather-app {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 20px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.3);
            width: 400px;
            padding: 30px;
            text-align: center;
            animation: fadeIn 0.7s ease-out;
        }

        @keyframes fadeIn {
            from {
                opacity: 0;
                transform: translateY(20px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

        .weather-app h1 {
            font-size: 28px;
            margin-bottom: 20px;
            color: #007BFF;
            text-shadow: 1px 1px 3px rgba(0, 0, 0, 0.2);
        }

        .back {
            text-decoration: none;
            color: #007BFF;
            font-weight: 600;
            margin-bottom: 15px;
            display: inline-block;
            transition: color 0.3s;
        }

        .back:hover {
            color: #0056b3;
        }

        .search {
            display: flex;
            gap: 10px;
            flex-wrap: wrap;
            justify-content: center;
            margin-bottom: 20px;
        }

        .search input {
            padding: 10px 15px;
            border: 2px solid #007BFF;
            border-radius: 25px;
            font-size: 16px;
            outline: none;
            flex-grow: 1;
            max-width: 180px;
            transition: all 0.3s;
        }

        .search input:focus {
            border-color: #0056b3;
            box-shadow: 0 0 10px rgba(0, 123, 255, 0.6);
        }

        .search button {
            padding: 10px 15px;
            border: none;
            border-radius: 25px;
            background-color: #007BFF;
            color: white;
            font-size: 14px;
            cursor: pointer;
            transition: all 0.3s ease;
            box-shadow: 0 5px 15px rgba(0, 123, 255, 0.3);
        }

        .search button:hover {
            background-color: #0056b3;
            transform: scale(1.05);
        }

        .weather-info {
            text-align: left;
            background: rgba(240, 248, 255, 0.8);
            padding: 20px;
            border-radius: 15px;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.1);
        }

        .weather-info h2 {
            font-size: 22px;
            color: #333;
            margin-bottom: 15px;
        }

        .weather-info p {
            font-size: 16px;
            margin: 8px 0;
            color: #555;
        }

        .weather-info img {
            display: block;
            margin: 0 auto 15px auto;
            width: 80px;
        }

        .search-history p {
            font-size: 14px;
            color: #007BFF;
            cursor: pointer;
            transition: color 0.3s;
        }

        .search-history p:hover {
            color: #0056b3;
        }

        #clock {
            position: absolute;
            top: 15px;
            right: 15px;
            font-size: 16px;
            color: white;
            font-weight: bold;
            background: rgba(0, 0, 0, 0.5);
            padding: 5px 10px;
            border-radius: 8px;
        }

        #loading-spinner {
            display: none;
            font-size: 18px;
            color: #007BFF;
        }

        /* Responsive Styling */
        @media (max-width: 500px) {
            .weather-app {
                width: 90%;
                padding: 20px;
            }

            .weather-info {
                padding: 15px;
            }

            .search input {
                max-width: 100%;
            }
        }
    </style>
</head>
<body>
    <div id="loading-spinner">Loading...</div>
    <div id="clock"></div> <!-- Clock Element -->
    <div class="weather-app">
        <a class="back" href="/">Back to Home</a>
        <h1>Weather App</h1>
        <div class="search">
            <input type="text" id="city-input" placeholder="Enter city">
            <button id="search-btn"><i class="fa-solid fa-magnifying-glass"></i> Search</button>
            <button id="current-location-btn">Use Current Location</button>
            <button id="unit-toggle">°C/°F</button>
            <button id="dark-mode-toggle">Dark Mode</button>
        </div>
        <div class="weather-info">
            <h2 id="city-name"></h2>
            <img id="weather-icon" src="" alt="Weather Icon" style="display: none;">
            <p id="temp"></p>
            <p id="description"></p>
            <p id="humidity"></p>
            <p id="wind"></p>
            <p id="day-night"></p>
            <div id="forecast"></div>
            <div id="search-history"></div>
        </div>
    </div>
    <script>
        const apiKey = 'f859e86f6183ffda99e0935e356a15ec'; // Your API key here
        let unit = 'metric';
        let darkMode = false;

        document.getElementById('search-btn').addEventListener('click', () => {
            const city = document.getElementById('city-input').value;
            if (city) {
                getWeather(city);
                saveSearch(city);
            }
        });

        document.getElementById('current-location-btn').addEventListener('click', () => {
            if (navigator.geolocation) {
                navigator.geolocation.getCurrentPosition((position) => {
                    const { latitude, longitude } = position.coords;
                    getWeatherByCoordinates(latitude, longitude);
                });
            } else {
                alert('Geolocation is not supported by this browser.');
            }
        });

        document.getElementById('unit-toggle').addEventListener('click', () => {
            unit = unit === 'metric' ? 'imperial' : 'metric';
            const city = document.getElementById('city-name').innerText;
            if (city) {
                getWeather(city);
            }
        });

        document.getElementById('dark-mode-toggle').addEventListener('click', () => {
            darkMode = !darkMode;
            document.body.classList.toggle('dark-mode', darkMode);
            document.querySelector('.weather-app').classList.toggle('dark-mode', darkMode);
            document.querySelectorAll('.weather-info p').forEach(p => p.classList.toggle('dark-mode', darkMode));
        });

        function showLoading() {
            document.getElementById('loading-spinner').style.display = 'block';
        }

        function hideLoading() {
            document.getElementById('loading-spinner').style.display = 'none';
        }

        function getWeather(city) {
            showLoading();
            fetch(`https://api.openweathermap.org/data/2.5/weather?q=${city}&appid=${apiKey}&units=${unit}`)
                .then(response => response.json())
                .then(data => {
                    displayWeather(data);
                    hideLoading();
                })
                .catch(error => {
                    alert('Failed to fetch weather data');
                    hideLoading();
                });
        }

        function getWeatherByCoordinates(latitude, longitude) {
            showLoading();
            fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${latitude}&lon=${longitude}&appid=${apiKey}&units=${unit}`)
                .then(response => response.json())
                .then(data => {
                    displayWeather(data);
                    hideLoading();
                })
                .catch(error => {
                    alert('Failed to fetch weather data');
                    hideLoading();
                });
        }

        function displayWeather(data) {
            const cityName = document.getElementById('city-name');
            const temp = document.getElementById('temp');
            const description = document.getElementById('description');
            const humidity = document.getElementById('humidity');
            const wind = document.getElementById('wind');
            const dayNight = document.getElementById('day-night');
            const weatherIcon = document.getElementById('weather-icon');

            cityName.innerText = data.name;
            temp.innerText = `Temperature: ${data.main.temp} °${unit === 'metric' ? 'C' : 'F'}`;
            description.innerText = `Description: ${data.weather[0].description}`;
            humidity.innerText = `Humidity: ${data.main.humidity}%`;
            wind.innerText = `Wind Speed: ${data.wind.speed} ${unit === 'metric' ? 'm/s' : 'mph'}`;
            dayNight.innerText = data.dt > data.sys.sunset ? 'Night' : 'Day';
            weatherIcon.src = `http://openweathermap.org/img/w/${data.weather[0].icon}.png`;
            weatherIcon.style.display = 'block';
        }

        function saveSearch(city) {
            let history = JSON.parse(localStorage.getItem('searchHistory')) || [];
            history.push(city);
            if (history.length > 5) history.shift();
            localStorage.setItem('searchHistory', JSON.stringify(history));
            displaySearchHistory();
        }

        function displaySearchHistory() {
            const searchHistory = JSON.parse(localStorage.getItem('searchHistory')) || [];
            const historyDiv = document.getElementById('search-history');
            historyDiv.innerHTML = '';
            searchHistory.forEach(city => {
                const p = document.createElement('p');
                p.innerText = city;
                p.addEventListener('click', () => getWeather(city));
                historyDiv.appendChild(p);
            });
        }

        displaySearchHistory(); // Initialize with saved search history

        // Clock functionality
        function updateClock() {
            const clockElement = document.getElementById('clock');
            const now = new Date();
            const hours = now.getHours().toString().padStart(2, '0');
            const minutes = now.getMinutes().toString().padStart(2, '0');
            const seconds = now.getSeconds().toString().padStart(2, '0');
            clockElement.innerText = `${hours}:${minutes}:${seconds}`;
        }

        setInterval(updateClock, 1000); // Update the clock every second
        updateClock(); // Initial call to set the clock immediately
        function updateClock() {
    const clockElement = document.getElementById('clock');
    const now = new Date();
    let hours = now.getHours();
    const minutes = now.getMinutes().toString().padStart(2, '0');
    const seconds = now.getSeconds().toString().padStart(2, '0');
    
    // Determine A.M. or P.M.
    const amPm = hours >= 12 ? 'P.M.' : 'A.M.';
    
    // Convert 24-hour time to 12-hour format
    hours = hours % 12 || 12;
    
    clockElement.innerText = `${hours}:${minutes}:${seconds} ${amPm}`;
}

setInterval(updateClock, 1000); // Update the clock every second
updateClock(); // Initial call to set the clock immediately

    </script>
</body>
</html>
