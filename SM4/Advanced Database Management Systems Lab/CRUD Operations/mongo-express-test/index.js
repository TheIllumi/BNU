const express = require('express');
const mongoose = require('mongoose');

const app = express();
app.use(express.json());

// MongoDB connection
mongoose.connect('mongodb://localhost:27017/testdb')

.then(() => console.log("✅ Connected to MongoDB"))
.catch(err => console.error("❌ Connection error:", err));

// Simple schema
const userSchema = new mongoose.Schema({ name: String });
const User = mongoose.model('User', userSchema);

// Routes
app.get('/', (req, res) => res.send('Hello from Express + MongoDB!'));

app.post('/add-user', async (req, res) => {
    const newUser = new User({ name: req.body.name || 'Test User' });
    await newUser.save();
    res.send('✅ User added!');
});

app.get('/users', async (req, res) => {
    const users = await User.find();
    res.json(users);
});

app.listen(3000, () => {
    console.log('🚀 Server running on http://localhost:3000');
});
