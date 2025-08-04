document.querySelector('.delete-btn').addEventListener('click', function(event) {
    if (!confirm("Are you sure you want to delete this patient?")) {
        event.preventDefault();
    }
});