// Train body
#define BODY_WIDTH 0.5f
#define BODY_HEIGHT 0.75f
#define BODY_LENGTH 2.0f
#define BODY_X 0.0f
#define BODY_Y 1.25f
#define BODY_Z 0.0f
vmath::vec4 body_color = { 1.0f, 0.0f, 0.0f, 1.0f };

// Engineer's compartment
#define ENG_WIDTH 0.5f
#define ENG_HEIGHT 0.5f
#define ENG_LENGTH 0.75f
#define ENG_X BODY_X
#define ENG_Y (BODY_Y + BODY_HEIGHT + ENG_HEIGHT)
#define ENG_Z (BODY_Z + BODY_LENGTH - ENG_LENGTH)
vmath::vec4 eng_color = { 0.0f, 1.0f, 0.0f, 1.0f };

// Smoke stack
#define STACK_RADIUS 0.25f
#define STACK_HEIGHT 0.5f
#define FUNNEL_RADIUS 0.5f
#define FUNNEL_HEIGHT 0.5f
#define STACK_X BODY_X
#define STACK_Y (BODY_Y + BODY_HEIGHT)
#define STACK_Z (-BODY_LENGTH/4.0f - STACK_RADIUS)
vmath::vec4 stack_color = { 1.0f, 1.0f, 0.0f, 1.0f };
vmath::vec4 smoke_color = { 0.45f, 0.51f, 0.46f, 1.0f };

// Wheels
#define WHEEL_RADIUS 0.45f
#define WHEEL_WIDTH 0.3f
#define WHEEL_X (BODY_X + BODY_WIDTH + WHEEL_WIDTH/2)
#define WHEEL_Y (BODY_Y - BODY_HEIGHT)
#define WHEEL_Z (BODY_Z + BODY_LENGTH - (WHEEL_RADIUS + WHEEL_WIDTH/2.0f))
#define MID_WHEEL_OFFSET (2.0f*(WHEEL_RADIUS + WHEEL_WIDTH))
#define SPOKE_WIDTH (0.1f*WHEEL_WIDTH)
#define SPOKE_LENGTH WHEEL_RADIUS
vmath::vec4 wheel_color = {0.0f, 0.0f, 0.0f, 1.0f};

// Track
#define RAIL_WIDTH 0.125f
#define RAIL_HEIGHT 0.125f
#define RAIL_LENGTH 11.0f
#define RAIL_OFFSET_X 0.625f
#define RAIL_OFFSET_Y -RAIL_HEIGHT
#define RAIL_OFFSET_Z 0.0f
vmath::vec4 rail_color = {0.5f, 0.5f, 0.5f, 1.0f};
vmath::vec4 ties_color = {0.8f, 0.3f, 0.3f, 1.0f};

// Ties
#define RAIL_TIES_WIDTH 0.125f
#define RAIL_TIES_HEIGHT 0.125f
#define RAIL_TIES_LENGTH 1.5f
#define RAIL_TIES_OFFSET_X 0.0f
#define RAIL_TIES_OFFSET_Y -RAIL_HEIGHT-RAIL_TIES_HEIGHT
#define RAIL_TIES_OFFSET_Z 0.0f

// Blocks
#define BOTTOM_BLOCK_SIZE 2.0f
#define MIDDLE_BLOCK_SIZE 1.0f
#define TOP_BLOCK_SIZE 0.5f
vmath::vec4 bottom_color = {1.0f, 0.0f, 1.0f, 1.0f};
vmath::vec4 middle_color = {0.0f, 1.0f, 0.0f, 1.0f};
vmath::vec4 top_color = {0.5f, 0.5f, 1.0f, 1.0f};
