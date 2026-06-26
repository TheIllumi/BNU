// SPDX-License-Identifier: MIT
pragma solidity ^0.8.19;

/**
 * @title TodoContract
 * @notice Decentralized task management on Ethereum Sepolia Testnet
 * @dev Web3 To-Do Contract — BNU Digital Finance & Blockchain Technologies
 *      Team: Saad Mughal, Khadijah Zahoor, Sara Haider, Syed Shahmeer Bakht
 */
contract TodoContract {

    // =========================================================
    //  DATA STRUCTURES
    // =========================================================

    struct Task {
        string  content;      // Task description (max 280 bytes)
        bool    isCompleted;  // false = pending | true = done
        address owner;        // Wallet that created this task
    }

    uint256 public taskCount;                          // Auto-incrementing ID counter
    mapping(uint256 => Task)       public tasks;       // taskId => Task
    mapping(address => uint256[]) private ownerTasks;  // wallet => [taskIds]

    // =========================================================
    //  EVENTS
    // =========================================================

    event TaskCreated(uint256 indexed id, address indexed owner, string content);
    event TaskToggled(uint256 indexed id, bool isCompleted);
    event TaskEdited(uint256 indexed id, string newContent);
    event TaskDeleted(uint256 indexed id);

    // =========================================================
    //  MODIFIERS
    // =========================================================

    modifier onlyOwner(uint256 _id) {
        require(tasks[_id].owner == msg.sender, "Not the task owner");
        _;
    }

    modifier taskExists(uint256 _id) {
        require(_id > 0 && _id <= taskCount, "Task does not exist");
        require(tasks[_id].owner != address(0), "Task has been deleted");
        _;
    }

    // =========================================================
    //  CREATE
    // =========================================================

    /**
     * @notice Create a new task linked to the caller's wallet.
     * @param _content The task description (1–280 bytes).
     */
    function createTask(string memory _content) public {
        require(bytes(_content).length > 0,   "Task cannot be empty");
        require(bytes(_content).length <= 280, "Content too long (max 280 chars)");

        taskCount++;                    // IDs start at 1

        tasks[taskCount] = Task({
            content:     _content,
            isCompleted: false,
            owner:       msg.sender    // EVM supplies caller identity
        });

        ownerTasks[msg.sender].push(taskCount);

        emit TaskCreated(taskCount, msg.sender, _content);
    }

    // =========================================================
    //  READ
    // =========================================================

    /**
     * @notice Fetch a single task by ID.
     * @return content     The task text.
     * @return isCompleted Whether the task is done.
     * @return owner       The wallet that owns this task.
     */
    function getTask(uint256 _id)
        public
        view
        taskExists(_id)
        returns (string memory content, bool isCompleted, address owner)
    {
        Task storage t = tasks[_id];
        return (t.content, t.isCompleted, t.owner);
    }

    /**
     * @notice Return all task IDs belonging to the caller.
     * @dev Frontend uses these IDs to batch-call getTask().
     */
    function getMyTasks() public view returns (uint256[] memory) {
        return ownerTasks[msg.sender];
    }

    // =========================================================
    //  UPDATE — Toggle completion
    // =========================================================

    /**
     * @notice Flip a task's completion status (pending ↔ done).
     * @param _id The ID of the task to toggle.
     */
    function toggleTask(uint256 _id)
        public
        taskExists(_id)
        onlyOwner(_id)
    {
        tasks[_id].isCompleted = !tasks[_id].isCompleted;
        emit TaskToggled(_id, tasks[_id].isCompleted);
    }

    // =========================================================
    //  UPDATE — Edit content
    // =========================================================

    /**
     * @notice Replace the text of an existing task.
     * @param _id         The ID of the task to edit.
     * @param _newContent The replacement text (1–280 bytes).
     */
    function editTask(uint256 _id, string memory _newContent)
        public
        taskExists(_id)
        onlyOwner(_id)
    {
        require(bytes(_newContent).length > 0,   "Content cannot be empty");
        require(bytes(_newContent).length <= 280, "Content too long (max 280 chars)");

        tasks[_id].content = _newContent;
        emit TaskEdited(_id, _newContent);
    }

    // =========================================================
    //  DELETE
    // =========================================================

    /**
     * @notice Reset a task to default values (soft-delete).
     * @dev    Blockchain storage is immutable; resetting to defaults is the
     *         gas-efficient equivalent of deletion. The zeroed record remains
     *         auditable on-chain, which is intentional by design.
     * @param _id The ID of the task to delete.
     */
    function deleteTask(uint256 _id)
        public
        taskExists(_id)
        onlyOwner(_id)
    {
        delete tasks[_id];   // Resets all fields to Solidity defaults
        emit TaskDeleted(_id);
    }

    // =========================================================
    //  UTILITY
    // =========================================================

    /**
     * @notice Return the total number of tasks ever created (including deleted).
     */
    function getTotalTaskCount() public view returns (uint256) {
        return taskCount;
    }
}
