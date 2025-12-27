import streamlit as st

# Title of the app
st.title("Simple Calculator")

# Input fields
num1 = st.number_input("Enter the first number", step=1.0)
num2 = st.number_input("Enter the second number", step=1.0)

# Dropdown to select the operation
operation = st.selectbox("Select operation", ("Add", "Subtract", "Multiply", "Divide"))

# Calculate based on the selected operation
if st.button("Calculate"):
    if operation == "Add":
        result = num1 + num2
        st.success(f"The result is: {result}")
    elif operation == "Subtract":
        result = num1 - num2
        st.success(f"The result is: {result}")
    elif operation == "Multiply":
        result = num1 * num2
        st.success(f"The result is: {result}")
    elif operation == "Divide":
        if num2 != 0:
            result = num1 / num2
            st.success(f"The result is: {result}")
        else:
            st.error("Division by zero is not allowed.")
