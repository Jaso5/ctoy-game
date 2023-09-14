use rapier3d::{prelude::{
    BroadPhase, CCDSolver, ColliderSet, ImpulseJointSet, IntegrationParameters, IslandManager,
    MultibodyJointSet, NarrowPhase, PhysicsPipeline, RigidBodySet,
}, na::Vector3};

#[allow(unused)]
pub struct PhysicsCtx {
    gravity: Vector3<f32>,

    rigid_body_set: RigidBodySet,
    collider_set: ColliderSet,

    integration_params: IntegrationParameters,
    physics_pipeline: PhysicsPipeline,
    island_manager: IslandManager,
    broad_phase: BroadPhase,
    narrow_phase: NarrowPhase,
    implulse_joint_set: ImpulseJointSet,
    multibody_joint_set: MultibodyJointSet,
    ccd_solver: CCDSolver,
    physics_hooks: (), // Box<dyn PhysicsHooks>,
    event_handler: (), // Box<dyn EventHandler>
}

impl PhysicsCtx {
    pub fn new(gravity: Vector3<f32>) -> Self {
        Self {
            gravity,

            rigid_body_set: RigidBodySet::new(),
            collider_set: ColliderSet::new(),

            integration_params: IntegrationParameters::default(),
            physics_pipeline: PhysicsPipeline::new(),
            island_manager: IslandManager::new(),
            broad_phase: BroadPhase::new(),
            narrow_phase: NarrowPhase::new(),
            implulse_joint_set: ImpulseJointSet::new(),
            multibody_joint_set: MultibodyJointSet::new(),
            ccd_solver: CCDSolver::new(),
            physics_hooks: (),
            event_handler: (),
        }
    }
}
