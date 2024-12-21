const express = require('express');
const path = require('path');
const app = express();
const PORT = process.env.PORT || 4500;
const dotenv = require("dotenv")
dotenv.config();

// Set EJS as the view engine
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

// Serve static files (like CSS and JavaScript)
app.use(express.static(path.join(__dirname, 'public')));

// Home route - landing page with calculator
app.get('/', (req, res) => {
  res.render('index');
});

app.get('/calculator', (req, res) => {
    res.render('calculator');
  });

  app.get("/weather", (req, res) => {
    res.render("weather")
  })

// Route for YouTube Thumbnail Downloader
app.get('/thumbnaildownloader', (req, res) => {
  res.render('thumbnaildownloader');
});

// Start the server
app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});
