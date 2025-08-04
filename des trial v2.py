import simpy
import numpy as np
import random

class Inventory:
    def __init__(self, capacity):
        self.capacity = capacity
        self.stock = 0

    def restock(self, amount):
        prev_stock = self.stock
        self.stock = min(self.stock + amount, self.capacity)
        print(f" - Restocked {amount} units (from {prev_stock} to {self.stock})")

    def sell(self, demand):
        if self.stock >= demand:
            self.stock -= demand
            print(f" - Sold {demand} units. Stock left: {self.stock}")
        else:
            print(f" - Only {self.stock} units available, demand was {demand}. SOLD OUT!")
            self.stock = 0

class InventorySimulation:
    def __init__(self, simulation_seconds, restock_interval, max_restock_amount, max_demand, inventory_capacity):
        self.simulation_seconds = simulation_seconds
        self.restock_interval = restock_interval
        self.max_restock_amount = max_restock_amount
        self.max_demand = max_demand
        self.env = simpy.Environment()
        self.inventory = Inventory(inventory_capacity)
        self.stock_log = []

    def restock_process(self):
        while True:
            yield self.env.timeout(self.restock_interval)
            amount = random.randint(1, self.max_restock_amount)
            self.inventory.restock(amount)

    def customer_process(self):
        while True:
            yield self.env.timeout(random.randint(2, 6))
            demand = random.randint(1, self.max_demand)
            self.inventory.sell(demand)
            self.stock_log.append((self.env.now, self.inventory.stock))

    def run(self):
        self.env.process(self.restock_process())
        self.env.process(self.customer_process())
        self.env.run(until=self.simulation_seconds)

        # After simulation summary
        times, stocks = zip(*self.stock_log) if self.stock_log else ([], [])
        print("\nStock Over Time:")
        for t, s in zip(times, stocks):
            print(f"Time {t}s: Stock = {s}")

# Settings in seconds
SIMULATION_SECONDS = 120
RESTOCK_INTERVAL = 10
MAX_RESTOCK_AMOUNT = 20
MAX_CUSTOMER_DEMAND = 10
INVENTORY_CAPACITY = 100

# Run simulation
sim = InventorySimulation(
    simulation_seconds=SIMULATION_SECONDS,
    restock_interval=RESTOCK_INTERVAL,
    max_restock_amount=MAX_RESTOCK_AMOUNT,
    max_demand=MAX_CUSTOMER_DEMAND,
    inventory_capacity=INVENTORY_CAPACITY
)
sim.run()
